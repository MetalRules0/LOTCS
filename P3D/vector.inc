edge MACRO arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8

mov arg7, arg6

sub arg1, arg3
sub arg7, arg4
imul arg7, arg7, arg1

mov arg8, arg7
mov arg7, arg5

sub arg2, arg4
sub arg7, arg3
imul arg7, arg7, arg2

sub arg8, arg7

ENDM
