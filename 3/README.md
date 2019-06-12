$ make && ./compiler.exe test/iftest.c
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler
i = 0;
s = 0;
if (i < 1) {
    s = 3;
} else {
    s = 2;
}
========== lex ==============
token=i
token==
token=0
token=;
token=s
token==
token=0
token=;
token=if
token=(
token=i
token=<
token=1
token=)
token={
token=s
token==
token=3
token=;
token=}
token=else
token={
token=s
token==
token=2
token=;
token=}
========== dump ==============
0:i
1:=
2:0
3:;
4:s
5:=
6:0
7:;
8:if
9:(
10:i
11:<
12:1
13:)
14:{
15:s
16:=
17:3
18:;
19:}
20:else
21:{
22:s
23:=
24:2
25:;
26:}
============ parse =============
@0
D=A
@i
M=D

@0
D=A
@s
M=D

@i
D=M
@1
D=D-A
@L0
D;JGT

@3
D=A
@s
M=D

@L1
0;JMP

(L0)
@2
D=A
@s
M=D

(L1)
