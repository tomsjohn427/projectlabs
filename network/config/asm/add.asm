data segment
a dw 0202h
b dw 0408h
z dw ?
data ends

code segment
assume cs:code,ds:data
start:
mov ax,data
mov ds,ax
mov ax,a
mov bx,b
add ax,bx
mov z,ax
int 3
code ends
end start
