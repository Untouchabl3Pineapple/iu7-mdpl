EXTRN m: byte
EXTRN n: byte
EXTRN matrix: byte
EXTRN move_newline: near
EXTRN space: near

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODESEG
inp_row proc near
    mov ah, 1
    int 21h
    mov m, al
    sub m, '0'

    ret
inp_row endp

inp_col proc near
    mov ah, 1
    int 21h
    mov n, al
    sub n, '0'

    ret
inp_col endp

fill_matrix proc near
    mov al, m
    mul n
    mov cx, ax

    mov si, 0
    mov bx, 0

    fill_loop:
        mov ah, 1
        int 21h

        cmp al, 'A'
        jl change
        change_back:

        mov matrix[si][bx], al
        inc si

        call space

        mov ax, si
        mov dh, n
        div dh

        cmp ah, 0
        je newline
        newline_back:

        loop fill_loop

    ret

    change:
        add al, 'A' - '0'

        jmp change_back

    newline:
        call move_newline
        add bx, 9
        mov si, 0

        jmp newline_back
fill_matrix endp
CODESEG ENDS
END