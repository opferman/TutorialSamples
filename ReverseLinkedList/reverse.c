/*
 *
 *       Reverse Linked List
 *
 *
 */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#pragma pack(push)
#pragma pack(1)
typedef struct _NODE_ENTRY
{
    int Value;
    struct _NODE_ENTRY *pNext;
    struct _NODE_ENTRY *pPrev;
} NODE_ENTRY, *PNODE_ENTRY;
#pragma pack(pop)

extern PNODE_ENTRY ReverseAsm_LinkedList(PNODE_ENTRY pHead);
PNODE_ENTRY Reverse_LinkedList(PNODE_ENTRY pHead);
PNODE_ENTRY Reverse_Double(PNODE_ENTRY pHead);
void Reverse_DisplayListBothDirections(PNODE_ENTRY pNodeHead);

PNODE_ENTRY Reverse_CreateList(int Elements);
void Reverse_FreeList(PNODE_ENTRY pNodeHead);

void Reverse_DisplayList(PNODE_ENTRY pNodeHead);

int _cdecl main(int argc, char *argv[])
{
   int Index;
   PNODE_ENTRY pNodeHead = NULL;

   printf("Assembly Version\n");
   for (Index = 1; Index < 5; Index++) 
   {
       pNodeHead = Reverse_CreateList(Index);
       Reverse_DisplayList(pNodeHead);
       pNodeHead = ReverseAsm_LinkedList(pNodeHead);
       Reverse_DisplayList(pNodeHead);
       Reverse_FreeList(pNodeHead);
   }

   printf("C Version\n");
   for (Index = 1; Index < 5; Index++) 
   {
       pNodeHead = Reverse_CreateList(Index);
       Reverse_DisplayList(pNodeHead);
       pNodeHead = Reverse_LinkedList(pNodeHead);
       Reverse_DisplayList(pNodeHead);
       Reverse_FreeList(pNodeHead);
   }

   printf("Double Version\n");
   for (Index = 1; Index < 5; Index++) 
   {
       pNodeHead = Reverse_CreateList(Index);
       Reverse_DisplayListBothDirections(pNodeHead);
       pNodeHead = Reverse_Double(pNodeHead);
       Reverse_DisplayListBothDirections(pNodeHead);
       Reverse_FreeList(pNodeHead);
   }

   return 0;
}

void Reverse_FreeList(PNODE_ENTRY pNodeHead)
{
    PNODE_ENTRY pNodeWalker;

    if (pNodeHead) 
    {

        pNodeWalker = pNodeHead->pNext;

        while(pNodeWalker)
        {
            free(pNodeHead);

            pNodeHead = pNodeWalker;
            pNodeWalker = pNodeWalker->pNext;
        }

        free(pNodeHead);
    }
}

void Reverse_DisplayList(PNODE_ENTRY pNodeHead)
{
    PNODE_ENTRY pNodeWalker;

    if (pNodeHead) 
    {
        pNodeWalker = pNodeHead->pNext;

        while(pNodeWalker)
        {
            printf("%i, ", pNodeHead->Value);

            pNodeHead = pNodeWalker;
            pNodeWalker = pNodeWalker->pNext;
        }

        printf("%i\n\n", pNodeHead->Value);
    }
}



void Reverse_DisplayListBothDirections(PNODE_ENTRY pNodeHead)
{
    PNODE_ENTRY pNodeWalker;

    if (pNodeHead) 
    {
        pNodeWalker = pNodeHead->pNext;

        while(pNodeWalker)
        {
            printf("%i, ", pNodeHead->Value);

            pNodeHead = pNodeWalker;
            pNodeWalker = pNodeWalker->pNext;
        }

        printf("%i\n\n", pNodeHead->Value);

        pNodeWalker = pNodeHead->pPrev;

        while(pNodeWalker)
        {
            printf("%i, ", pNodeHead->Value);

            pNodeHead = pNodeWalker;
            pNodeWalker = pNodeWalker->pPrev;
        }

        printf("%i\n\n", pNodeHead->Value);
    }
}

PNODE_ENTRY Reverse_CreateList(int Elements)
{
    PNODE_ENTRY pNodeHead = NULL, pNodeWalker;
    int Index = 0;

    if (Elements != 0) 
    {
        pNodeHead = malloc(sizeof(NODE_ENTRY));
        pNodeHead->Value = Index++;
        pNodeHead->pNext = NULL;
        pNodeHead->pPrev = NULL;
        pNodeWalker = pNodeHead;

        while(--Elements) 
        {
            pNodeWalker->pNext = malloc(sizeof(NODE_ENTRY));
            pNodeWalker->pNext->pPrev = pNodeWalker;
            pNodeWalker = pNodeWalker->pNext;
            pNodeWalker->pNext = NULL;
            pNodeWalker->Value = Index++;
        }
    }

    return pNodeHead;
}

PNODE_ENTRY Reverse_LinkedList(PNODE_ENTRY pHead)
{
    PNODE_ENTRY pNode;
    PNODE_ENTRY pTemp;

    pNode = NULL;

    while (pHead) 
    {
        pTemp = pHead->pNext;
        pHead->pNext = pNode;
        pNode = pHead;
        pHead = pTemp;
    }
    
    return pNode;
}


PNODE_ENTRY Reverse_Double(PNODE_ENTRY pHead)
{
    if(pHead)
    {
        do
           {
                ((ULONG64)pHead->pPrev) ^= ((ULONG64)pHead->pNext);
                ((ULONG64)pHead->pNext) ^= ((ULONG64)pHead->pPrev);
                ((ULONG64)pHead->pPrev) ^= ((ULONG64)pHead->pNext);
                if(pHead->pPrev) pHead = pHead->pPrev;
            }   while(pHead->pPrev);
    }

    return pHead;
}
