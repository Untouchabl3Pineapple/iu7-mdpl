PUBLIC m
PUBLIC n
PUBLIC matrix

EXTRN inp_row: near
EXTRN inp_col: near
EXTRN fill_matrix: near
EXTRN print_matrix: near
EXTRN space: near
EXTRN move_newline: near

STK SEGMENT PARA STACK 'STACK'
    db 300 dup (0)
STK ENDS

DATASEG SEGMENT PARA COMMON 'DATA'
    inp_size_mes db "Input matrix rows and columns:$"
    inp_matrix_mes db "Input matrix:$"
    print_matrix_mes db "Matrix result:$"
    
    m db 1
    n db 1
    matrix db 101 DUP ('0')
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODESEG, DS:DATASEG, SS:STK
main:
    mov ax, DATASEG
    mov ds, ax

    mov ah, 9
    mov dx, offset inp_size_mes
    int 21h
    call move_newline

    call inp_row
    call space
    call inp_col

    call move_newline
    mov ah, 9
    mov dx, offset inp_matrix_mes
    int 21h

    call move_newline
    call fill_matrix

    mov ah, 9
    mov dx, offset print_matrix_mes
    int 21h
    call move_newline

    call print_matrix

    mov ax, 4c00h
    int 21h
CODESEG ENDS
END main
