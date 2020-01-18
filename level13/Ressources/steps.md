# Leve13

```
level13@SnowCrash:~$ ls -l
total 8
-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
```

The file is owned by the flag13 group and it's executable


```
level13@SnowCrash:~$ ./level13
UID 2013 started us but we we expect 4242
```

The program print an User Id and let us know that this program is executed with it, and the most important is that the program indicate which UID should be used

```
level13@SnowCrash:~$ id
uid=2013(level13) gid=2013(level13) groups=2013(level13),100(users)
```

Ok it's the level13 UID that it's used here

```
level13@SnowCrash:~$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/bin/sh
man:x:6:12:man:/var/cache/man:/bin/sh
lp:x:7:7:lp:/var/spool/lpd:/bin/sh
mail:x:8:8:mail:/var/mail:/bin/sh
news:x:9:9:news:/var/spool/news:/bin/sh
uucp:x:10:10:uucp:/var/spool/uucp:/bin/sh
proxy:x:13:13:proxy:/bin:/bin/sh
www-data:x:33:33:www-data:/var/www:/bin/sh
backup:x:34:34:backup:/var/backups:/bin/sh
list:x:38:38:Mailing List Manager:/var/list:/bin/sh
irc:x:39:39:ircd:/var/run/ircd:/bin/sh
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh
nobody:x:65534:65534:nobody:/nonexistent:/bin/sh
libuuid:x:100:101::/var/lib/libuuid:/bin/sh
syslog:x:101:103::/home/syslog:/bin/false
messagebus:x:102:106::/var/run/dbus:/bin/false
whoopsie:x:103:107::/nonexistent:/bin/false
landscape:x:104:110::/var/lib/landscape:/bin/false
sshd:x:105:65534::/var/run/sshd:/usr/sbin/nologin
level00:x:2000:2000::/home/user/level00:/bin/bash
level01:x:2001:2001::/home/user/level01:/bin/bash
level02:x:2002:2002::/home/user/level02:/bin/bash
level03:x:2003:2003::/home/user/level03:/bin/bash
level04:x:2004:2004::/home/user/level04:/bin/bash
level05:x:2005:2005::/home/user/level05:/bin/bash
level06:x:2006:2006::/home/user/level06:/bin/bash
level07:x:2007:2007::/home/user/level07:/bin/bash
level08:x:2008:2008::/home/user/level08:/bin/bash
level09:x:2009:2009::/home/user/level09:/bin/bash
level10:x:2010:2010::/home/user/level10:/bin/bash
level11:x:2011:2011::/home/user/level11:/bin/bash
level12:x:2012:2012::/home/user/level12:/bin/bash
level13:x:2013:2013::/home/user/level13:/bin/bash
level14:x:2014:2014::/home/user/level14:/bin/bash
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
flag04:x:3004:3004::/home/flag/flag04:/bin/bash
flag05:x:3005:3005::/home/flag/flag05:/bin/bash
flag06:x:3006:3006::/home/flag/flag06:/bin/bash
flag07:x:3007:3007::/home/flag/flag07:/bin/bash
flag08:x:3008:3008::/home/flag/flag08:/bin/bash
flag09:x:3009:3009::/home/flag/flag09:/bin/bash
flag10:x:3010:3010::/home/flag/flag10:/bin/bash
flag11:x:3011:3011::/home/flag/flag11:/bin/bash
flag12:x:3012:3012::/home/flag/flag12:/bin/bash
flag13:x:3013:3013::/home/flag/flag13:/bin/bash
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
```

```
level13@SnowCrash:~$ cat /etc/passwd | grep 4242
```

Ther's no user withe the 4242 UID...

Let's try with strings

```
...
exit
strdup
printf
getuid
...
...
...
UID %d started us but we we expect %d
boe]!ai0FB@.:|L6l@A?>qJ}I
your token is %s
...
```

Let's try with gdb also, so here we are adding a breakpoint to the main to get the address
add Examining the mem 

```
level13@SnowCrash:~$ gdb level13
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level13/level13...(no debugging symbols found)...done.
(gdb) break main
Breakpoint 1 at 0x804858f


disassemble main
or
(gdb) x/21 i main                         # /size format   addr/name_funtion
   0x804858c <main>:	push   %ebp
   0x804858d <main+1>:	mov    %esp,%ebp
   0x804858f <main+3>:	and    $0xfffffff0,%esp
   0x8048592 <main+6>:	sub    $0x10,%esp
   0x8048595 <main+9>:	call   0x8048380 <getuid@plt>
   0x804859a <main+14>:	cmp    $0x1092,%eax
   0x804859f <main+19>:	je     0x80485cb <main+63>
   0x80485a1 <main+21>:	call   0x8048380 <getuid@plt>
   0x80485a6 <main+26>:	mov    $0x80486c8,%edx
   0x80485ab <main+31>:	movl   $0x1092,0x8(%esp)
   0x80485b3 <main+39>:	mov    %eax,0x4(%esp)
   0x80485b7 <main+43>:	mov    %edx,(%esp)
   0x80485ba <main+46>:	call   0x8048360 <printf@plt>
   0x80485bf <main+51>:	movl   $0x1,(%esp)
   0x80485c6 <main+58>:	call   0x80483a0 <exit@plt>
   0x80485cb <main+63>:	movl   $0x80486ef,(%esp)
   0x80485d2 <main+70>:	call   0x8048474 <ft_des>
   0x80485d7 <main+75>:	mov    $0x8048709,%edx
   0x80485dc <main+80>:	mov    %eax,0x4(%esp)
   0x80485e0 <main+84>:	mov    %edx,(%esp)
   0x80485e3 <main+87>:	call   0x8048360 <printf@plt>
```


%XXX  >> registre       >> p/x $XXX          >> set $XXX = val
$0x.. >> value          >> p/x 0x..
0x..  >> address        >> p/x *addr         >> set var 0x...= val


The program get the uid of the current user and stock the return val in the $eax register 
```
   0x8048595 <main+9>:	call   0x8048380 <getuid@plt>
```

here the proram check if the val in the eax is equal to 0X1092

```
   0x804859a <main+14>:	cmp    $0x1092,%eax
```
We can see that the 0X1092 is the 4242 val seen before when we did execute the program 

So we set a breakpoint in the lvl of the cmp inst
```
   b *0x0804859a
```
run the program

```
   run
   (gdb) disassemble main
   Dump of assembler code for function main:
      0x0804858c <+0>:	push   %ebp
      0x0804858d <+1>:	mov    %esp,%ebp
      0x0804858f <+3>:	and    $0xfffffff0,%esp
      0x08048592 <+6>:	sub    $0x10,%esp
      0x08048595 <+9>:	call   0x8048380 <getuid@plt>
   => 0x0804859a <+14>:	cmp    $0x1092,%eax
      0x0804859f <+19>:	je     0x80485cb <main+63>
      0x080485a1 <+21>:	call   0x8048380 <getuid@plt>
      0x080485a6 <+26>:	mov    $0x80486c8,%edx
      0x080485ab <+31>:	movl   $0x1092,0x8(%esp)
      0x080485b3 <+39>:	mov    %eax,0x4(%esp)
      0x080485b7 <+43>:	mov    %edx,(%esp)
      0x080485ba <+46>:	call   0x8048360 <printf@plt>
      0x080485bf <+51>:	movl   $0x1,(%esp)
      0x080485c6 <+58>:	call   0x80483a0 <exit@plt>
      0x080485cb <+63>:	movl   $0x80486ef,(%esp)
      0x080485d2 <+70>:	call   0x8048474 <ft_des>
      0x080485d7 <+75>:	mov    $0x8048709,%edx
      0x080485dc <+80>:	mov    %eax,0x4(%esp)
      0x080485e0 <+84>:	mov    %edx,(%esp)
      0x080485e3 <+87>:	call   0x8048360 <printf@plt>
      0x080485e8 <+92>:	leave
      0x080485e9 <+93>:	ret
   End of assembler dump.
```

```
gdb) p/x $eax
$4 = 0x7dd
```
0x7dd is the iud of the level13 user, so w'll updat the EAX register to the 0x1092 val

```
(gdb) set $eax=4242
(gdb) c
Continuing.
your token is 2A31L79asukciNyi8uppkEuSx
[Inferior 1 (process 1942) exited with code 050]
```

and Bingo