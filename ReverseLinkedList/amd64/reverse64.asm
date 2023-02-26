;
;  Reverse Linked List.
;
;
;

include ksamd64.inc

_NODE_ENTRY_ASM STRUCT

    Value dd <?>
    pNext dq <?>

_NODE_ENTRY_ASM ENDS

public ReverseAsm_LinkedList

       NESTED_ENTRY ReverseAsm_LinkedList, _TEXT$00
              ADD RSP, 8
              END_PROLOGUE 
              XOR RDX, RDX     ; RDX will be our "previous"
@ReverseLoop:
             TEST RCX, RCX
             JZ @ExitLoop
             MOV R8, _NODE_ENTRY_ASM.pNext[RCX]   ; Save Node->pNext
             MOV _NODE_ENTRY_ASM.pNext[RCX], RDX  ; Point Node->pNext to Previous
             MOV RDX, RCX                         ; Previous = Head
             MOV RCX, R8                          ; Head = Node->pNext
             JMP @ReverseLoop
@ExitLoop:
              MOV RAX, RDX     ; Return the new head
              SUB RSP, 8
              RET

       NESTED_END ReverseAsm_LinkedList, _TEXT$00

end