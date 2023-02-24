#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


int printf_new(char *pszFormatString, ...);
int printf_manual(char *pszFormatString, ...);

int _cdecl main(int argc, char *argv[])
{
   printf_new(argv[0]);
   printf_new("\nHello\n");
   printf_new("Test String %s with integer %i and %% test\n", argv[0], argc);

   printf_manual(argv[0]);
   printf_manual("\nHello\n");
   printf_manual("Test String %s with integer %i and %% test\n", argv[0], argc);

   return 0;
}


int  printf_new(char *pszFormatString, ...)
{
   int CharacterCount = 0;
   int PrintInteger;
   char IntegerString[10];
   char *pPrintString;
   va_list VaList;

   va_start(VaList, pszFormatString);
   
   while(*pszFormatString)
   {
       if(*pszFormatString == '%')
       {
           pszFormatString++;
           switch(*pszFormatString)
           {
              case 's': 
                      pPrintString = va_arg(VaList, char *);
                      fputs(pPrintString, stdout);
                      pszFormatString++;
                      CharacterCount += strlen(pPrintString);
                      break;
              case 'i':  
                      PrintInteger = va_arg(VaList, int);
                      _itoa(PrintInteger, IntegerString, 10);
                      fputs(IntegerString, stdout);
                      pszFormatString++;
                      CharacterCount += strlen(IntegerString);
                      break;
              case '%': 
                      putchar('%');
                      pszFormatString++;
                      CharacterCount++;
                      break;
              case '\0': 
                      break;
              default:
                      putchar('%');
                      putchar(*pszFormatString);
                      pszFormatString++;            
                      CharacterCount +=2;
           }       
       }
       else
       {
           putchar(*pszFormatString);
           pszFormatString++;
           CharacterCount++;
       }
   }

   va_end(VaList);

   return CharacterCount;
}

int printf_manual(char *pszFormatString, ...)
{
   int CharacterCount = 0;
   int PrintInteger;
   char IntegerString[10];
   char *pPrintString;
   void *StackLocation;

   StackLocation = &pszFormatString;
   StackLocation = ((void **)StackLocation) + 1; 
   
   while(*pszFormatString)
   {
       if(*pszFormatString == '%')
       {
           pszFormatString++;
           switch(*pszFormatString)
           {
              case 's': 
                      pPrintString = (char *)*((char **)StackLocation);
                      StackLocation = ((void **)StackLocation) + 1; 
                      fputs(pPrintString, stdout);
                      pszFormatString++;
                      CharacterCount += strlen(pPrintString);
                      break;
              case 'i':  
                      PrintInteger = (int)*((int *)StackLocation);
                      StackLocation = ((void **)StackLocation) + 1; 
                      _itoa(PrintInteger, IntegerString, 10);
                      fputs(IntegerString, stdout);
                      pszFormatString++;
                      CharacterCount += strlen(IntegerString);
                      break;
              case '%': 
                      putchar('%');
                      pszFormatString++;
                      CharacterCount++;
                      break;
              case '\0': 
                      break;
              default:
                      putchar('%');
                      putchar(*pszFormatString);
                      pszFormatString++;            
                      CharacterCount +=2;
           }       
       }
       else
       {
           putchar(*pszFormatString);
           pszFormatString++;
           CharacterCount++;
       }
   }

   return CharacterCount;
}


