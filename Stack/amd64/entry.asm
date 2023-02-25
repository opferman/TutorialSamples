;*********************************************************
; Testing Application
;
;  Written in Assembly x64
; 
;
;*********************************************************

include ksamd64.inc


;*********************************************************
; Included Files
;*********************************************************
extern ExitProcess:proc
extern printf:proc

.DATA
 szFinalFormatString   db  "Final Answer %i", 0Dh, 0ah, 0
.CODE

;*********************************************************
; mainCRTStartup
;
;  The main entry point to the application.
;
;
;
;*********************************************************   
NESTED_ENTRY mainCRTStartup, _TEXT$00
  alloc_stack(8)
.ENDPROLOG 
  
  MOV R8, 2
  MOV RDX, 10
  MOV RCX, 20
  CALL Multiply_and_add                 ; X = Multiply_and_add(20, 10, 2) [60]

  MOV RCX, RAX
  MOV RDX, 10
  MOV R8, 6
  CALL AddThreeNumbers                  ; X = AddThreeNumbers(X, 10, 6)  [60 + 10 + 6] = 76
  
  MOV RDX, RAX
  MOV RCX, OFFSET szFinalFormatString   ; printf("Final Answer %i", X);
  CALL printf

@Entry_Exit:
  XOR RCX, RCX
  CALL ExitProcess
NESTED_END mainCRTStartup, _TEXT$00

;*********************************************************
; Multiply_and_add
;
;  Add Two Numbers and multiply
;
;
;
;********************************************************* 
NESTED_ENTRY Multiply_and_add, _TEXT$00
  alloc_stack(8)                        ;  int Z;
.ENDPROLOG 
  MOV [RSP], R8                         ; z = C;
  CALL AddTwoNumbers                    ; X = AddTwoNumbers(A, B)

  XOR RDX, RDX
  MUL QWORD PTR [RSP]                    ; return (X*C);

  ADD RSP, 8
  RET
NESTED_END Multiply_and_add, _TEXT$00


;*********************************************************
; AddTwoNumbers
;
;  Add Two Numbers
;
;
;
;********************************************************* 
NESTED_ENTRY AddTwoNumbers, _TEXT$00
  alloc_stack(8)                        ;  int Z;
.ENDPROLOG 

  MOV [RSP], RCX
  ADD [RSP], RDX
  MOV RAX, [RSP]                        ; return Z = A + B;

  ADD RSP, 8
  RET
NESTED_END AddTwoNumbers, _TEXT$00

;*********************************************************
; AddThreeNumbers
;
;  Add Three Numbers
;
;
;
;********************************************************* 
NESTED_ENTRY AddThreeNumbers, _TEXT$00
  alloc_stack(8*3)                      ; int Z, Y;
.ENDPROLOG 

  MOV [RSP], R8
  ADD [RSP], RCX                        ;  Z = A + C
  ADD [RSP + 10h], RDX                  ;  Y = Y + B          
  MOV RAX, [RSP]
  ADD RAX, [RSP + 10h]                  ;  return Z + Y

  ADD RSP, 8*3
  RET
NESTED_END AddThreeNumbers, _TEXT$00







END
