PUBLIC move_newline
PUBLIC print_matrix
PUBLIC space

EXTRN m: byte
EXTRN n: byte
EXTRN matrix: byte

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODESEG
move_newline proc near
    mov ah, 2
    mov dl, 10
    int 21h
    mov dl, 13
    int 21h

    ret
move_newline endp

space proc near
    mov ah, 2
    mov dl, " "
    int 21h

    ret
space endp

print_matrix proc near
    mov bl, m
    mov si, 0
    mov di, 9

    print_matrix_loop:
        mov cl, n

        print_row_loop:
            mov ah, 2
            mov dl, matrix[si]
            int 21h
            inc si

            call space

            loop print_row_loop

        call move_newline

        mov si, di
        add di, 9

        mov cl, bl
        dec bl

        loop print_matrix_loop

    ret
print_matrix endp
CODESEG ENDS
END
