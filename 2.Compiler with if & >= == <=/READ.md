$ gcc compiler.c lexer.c main.c -o test.exe

fangr@尻尻王 MSYS ~
$ ./test.exe test/iftest.c
i = 1;
s = 0;
if (i == 1) {
    s = 3;
} else {
    s = 2;
}
========== lex ==============
token=i
token==
token=1
token=;
token=s
token==
token=0
token=;
token=if
token=(
token=i
token===
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
2:1
3:;
4:s
5:=
6:0
7:;
8:if
9:(
10:i
11:==
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
t0 = 1
i = t0
t1 = 0
s = t1
t2 = i
t3 = 1
t4 = t2 == t3
ifnot t4 goto L0
t5 = 3
s = t5
goto L1
(L0)
t6 = 2
s = t6
(L1)
