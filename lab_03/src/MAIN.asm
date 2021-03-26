StkSeg  SEGMENT PARA STACK 'STACK'
        DB      200h DUP (?)
StkSeg  ENDS


DataS   SEGMENT WORD 'DATA'
HelloMessage    DB   13
                DB   10
                DB   'Hello, world !'
                DB   '$'
DataS   ENDS


CodeS   SEGMENT DWORD 'CODE'
        ASSUME  CS:CodeS, DS:DataS
CXInit:
        mov   CX,3
DispMsg:
        mov   AX,DataS
        mov   DS,AX
        mov   DX,OFFSET HelloMessage

        mov   AH,9
        int   21h
        mov   AH,7
        int   21h

        loop  DispMsg

        mov   AH,4Ch
        int   21h
CodeS   ENDS
        END   CXInit
        END   DispMsg
