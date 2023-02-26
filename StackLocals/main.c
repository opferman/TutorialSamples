#include <stdio.h>

void __declspec(noinline) ReadAString(void)
{
    char szInputString[256];

    fgets(szInputString, 256, stdin);
}

void __declspec(noinline) OutputAString(void)
{
    char szStackInput[256];

    printf(szStackInput);
    printf("\n");
}


int main(void)
{
    ReadAString();
    OutputAString();

    return 0;
}
