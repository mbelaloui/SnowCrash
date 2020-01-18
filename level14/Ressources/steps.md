string /bin/getflag

```
...
0123456
You should not reverse this
LD_PRELOAD
Injection Linked lib detected exit..
/etc/ld.so.preload
/proc/self/maps
/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..
libc
Check flag.Here is your token :
You are root are you that dumb ?
I`fA>_88eEd:=`85h0D8HE>,D
7`4Ci4=^d=J,?>i;6,7d416,7
<>B16\AD<C6,G_<1>^7ci>l4B
B8b:6,3fj7:,;bh>D@>8i:6@D
?4d@:,C>8C60G>8:h:Gb4?l,A
G8H.6,=4k5J0<cd/D@>>B:>:4
H8B8h_20B4J43><8>\ED<;j@3
78H:J4<4<9i_I4k0J^5>B1j`9
bci`mC{)jxkn<"uD~6%g7FK`7
Dc6m~;}f8Cj#xFkel;#&ycfbK
74H9D^3ed7k05445J0E4e;Da4
70hCi,E44Df[A4B/J@3f<=:`D
8_Dw"4#?+3i]q&;p6 gtw88EC
boe]!ai0FB@.:|L6l@A?>qJ}I
g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|
Nope there is no token here for you sorry. Try again :)
00000000 00:00 0
LD_PRELOAD detected through memory maps exit ..
;*2$"$
...
fputc@@GLIBC_2.0
afterSubstr
_Jv_RegisterClasses
isLib
fputs@@GLIBC_2.0
_init
ptrace@@GLIBC_2.0

```
We have got some interesting informations here

LD_PRELOAD a good concept we use this in malloc, to use our funtion instead of the real one 


```
I`fA>_88eEd:=`85h0D8HE>,D
7`4Ci4=^d=J,?>i;6,7d416,7
<>B16\AD<C6,G_<1>^7ci>l4B
B8b:6,3fj7:,;bh>D@>8i:6@D
?4d@:,C>8C60G>8:h:Gb4?l,A
G8H.6,=4k5J0<cd/D@>>B:>:4
H8B8h_20B4J43><8>\ED<;j@3
78H:J4<4<9i_I4k0J^5>B1j`9
bci`mC{)jxkn<"uD~6%g7FK`7
Dc6m~;}f8Cj#xFkel;#&ycfbK
74H9D^3ed7k05445J0E4e;Da4
70hCi,E44Df[A4B/J@3f<=:`D
8_Dw"4#?+3i]q&;p6 gtw88EC
boe]!ai0FB@.:|L6l@A?>qJ}I
```
Certemly the flags hashed we tryed md5 sha, caesar,... noting 


```
man ptrace

DESCRIPTION         top

       The ptrace() system call provides a means by which one process (the
       "tracer") may observe and control the execution of another process
       (the "tracee"), and examine and change the tracee's memory and
       registers.  It is primarily used to implement breakpoint debugging
       and system call tracing.

RETURN VALUE         top

       On success, the PTRACE_PEEK* requests return the requested data (but
       see NOTES), the PTRACE_SECCOMP_GET_FILTER request returns the number
       of instructions in the BPF program, and other requests return zero.

       On error, all requests return -1, and errno is set appropriately.
       Since the value returned by a successful PTRACE_PEEK* request may be
       -1, the caller must clear errno before the call, and then check it
       afterward to determine whether or not an error occurred.
```


gbd getflag, and go to the addre where the ptrace is 

```
    => 0x8048989 <main+67>:	call   0x8048540 <ptrace@plt>
    (gdb) p $eax
    $1 = 0
```
Nothing in our EAX yet, let's go to the next instruction

```
    (gdb) ni
    0x0804898e in main ()
    (gdb) p $eax
    $2 = -1
```
Like it's described in the man the ptrace return -1 if it's not possible to go further, so let's clear it.

```
    (gdb) set $eax=1
```

And it's great we can go further, so let's add a new breakPoint after the getuid of the user

```
    0x8048afd <main+439>:	call   0x80484b0 <getuid@plt>
```


```
    (gdb) break *0x8048afd
    Breakpoint 2 at 0x8048afd
    (gdb) ni        # to xecute the get uid 
```


Here we have the uid of the level 14, so let's change this with the uid of the flag 14 uid


```
cat /etc/passwd 
....
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
``

```
(gdb) set $eax=3014
(gdb) step
```

and bingo

```
(gdb) step
Single stepping until exit from function main,
which has no line number information.
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```

