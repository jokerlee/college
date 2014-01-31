typedef unsigned long ULONG; 

ULONG
FindBitFirstSetLeft (ULONG Number)
{
    __asm {
        bsr eax, Number
    }
}

ULONG
ClearBitsRightOf (ULONG Number)
{
    ULONG ulFirst = FindBitFirstSetLeft (Number);
    return Number & (0xffff << ulFirst);
}

int main(int argc, char* argv[])
{
    printf("%x\n", ClearBitsRightOf (0x07f7));
    return 0;
}

