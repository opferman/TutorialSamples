

#include "windows.h"
#include "stdio.h"

UINT Test_EntryFunction(UINT Value);
void Test_ExitFunction(UINT Value);
void Test_Inception(PVOID pReturnLocation);
void Test_Shim(void);
UINT Test_Inceptionx2(PVOID pReturnLocation, UINT ReturnValue);

typedef void (*PFN_INCEPTIONX2)(PVOID pReturnLocation, UINT ReturnValue);
typedef UINT (*PFN_ENTRY)(UINT Value);
typedef void (*PFN_EXIT)(UINT Value);
typedef UINT (*PFN_TESTTRICK)(void);

/**************************************************************** 
 *
 * main - The entry point to this wonderful application.
 * 
 *     Input: Nothing
 *     Return: Error Code
 * 
 * 
 ****************************************************************/
int main(void)
{
    UINT LocalVariable;
    PFN_ENTRY pfnEntry;
    PFN_EXIT pfnExit;

    pfnEntry = (PFN_ENTRY)GetProcAddress(NULL, "Test_EntryFunction");
    pfnExit = (PFN_EXIT)GetProcAddress(NULL, "Test_ExitFunction");

    LocalVariable = pfnEntry(5);

    pfnExit(LocalVariable);

    return 0;
}

/**************************************************************** 
 *
 * Test_EntryFunction - The first function called in our app
 * 
 *     Input: Nothing
 *     Return: Secret Value
 * 
 * 
 ****************************************************************/
UINT Test_EntryFunction(UINT Value)
{
    volatile ULONG64 *pItterateParameters;
    volatile ULONG64 OriginalReturnAddress;
    volatile ULONG64 *pThisIsInterceptAddress;
  
    pItterateParameters     = (((ULONG64*)&Value));
    pThisIsInterceptAddress = (((ULONG64*)&Value)-1);

    OriginalReturnAddress   = *pThisIsInterceptAddress;
    pItterateParameters[3] = OriginalReturnAddress;

    pItterateParameters[0] = (ULONG64)Test_Shim;
    pItterateParameters[1] = (ULONG64)Test_Shim;
    pItterateParameters[2] = (ULONG64)Test_Inception;

    *pThisIsInterceptAddress = (ULONG64)Test_Shim;
    printf("Test_EntryFunction %p, %I64u, %p, %p, %p, %p\n", pThisIsInterceptAddress, *pThisIsInterceptAddress,  pItterateParameters[0],  pItterateParameters[1],  pItterateParameters[2],  pItterateParameters[3]);

    return 0xDEADBEEF;
}


/**************************************************************** 
 *
 * Test_ExitFunction - The last function called in our app
 * 
 *     Input: Secret Value
 *     Return: Nothing
 * 
 * 
 ****************************************************************/
void Test_ExitFunction(UINT Value)
{
    printf("Test_ExitFunction(0x%0x)\n", Value);
}


/**************************************************************** 
 *
 * Test_Inception - The function to intercept the return.
 * 
 *     Input: Nothing
 *     Return: Nothing
 * 
 * 
 ****************************************************************/
void Test_Inception(PVOID pReturnLocation)
{
    PFN_INCEPTIONX2 pfnInceptionX2;
    PFN_TESTTRICK pfnTestTrick = (PFN_TESTTRICK)Test_Shim;

    ((ULONG)pReturnLocation) = pfnTestTrick();

    pfnInceptionX2 = (PFN_INCEPTIONX2)GetProcAddress(NULL, "Test_Inceptionx2");

    pfnInceptionX2((PVOID)&pReturnLocation, ((ULONG)pReturnLocation));
    printf("You should not see this.\n");
}

/**************************************************************** 
 *
 * Test_Inceptionx2 - The function to intercept the return.
 * 
 *     Input: Nothing
 *     Return: Nothing
 * 
 * 
 ****************************************************************/
UINT Test_Inceptionx2(PVOID pReturnLocation, UINT ReturnValue)
{
    volatile ULONG64 *pOriginalAddressLocation;
    volatile ULONG64 OriginalReturnAddress;
    volatile ULONG64 *pThisIsShimList;
  
    pOriginalAddressLocation  = (((ULONG64*)pReturnLocation)-1);
    OriginalReturnAddress     = *pOriginalAddressLocation;
    *((ULONG64*)pOriginalAddressLocation - 4) = OriginalReturnAddress;

    pThisIsShimList  = (((ULONG64*)&pReturnLocation)-1);
   
    for (;pThisIsShimList < ((ULONG64*)pOriginalAddressLocation - 4); pThisIsShimList++) 
    {
        *pThisIsShimList = (ULONG64)Test_Shim;
    }

    printf("Test_Inceptionx2 %p, %p, %p, %p\n", pThisIsShimList, pThisIsShimList -1, pThisIsShimList -2, pThisIsShimList -3);

    return ReturnValue;
}


/***************************************************************** 
 *
 * Test_Shim - Does Nothing
 * 
 *     Input: Nothing
 *     Return: Nothing
 * 
 * 
 ****************************************************************/
void Test_Shim(void)
{
    return;
}
    


/*************************************************************** 
 
  [          ]       [          ]         [ReturnOrig    ] Not  [ReturnOrig    ]
  [          ]       [          ]         [Test_Inception]      [  Unknown     ]
  [          ]       [          ]         [ReturnShim    ] Not  [              ]
  [          ]       [          ]         [ReturnShim    ] A    [              ]
  [  Return  ] ====> [ReturnShim]         [ReturnShim    ] Not  [ ReturnOrig   ]
  [  Align   ]       [  Align   ]                          A    [  ReturnShim  ]
                                                                [ ReturnShim   ]
                                                                [  Align       ]
 
 
                                            
                                            
                                            
                                            
 
 ****************************************************************/
