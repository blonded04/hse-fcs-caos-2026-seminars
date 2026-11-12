```
root@78fb3b794e4f:/work# cat /proc/self/maps
555555554000-555555556000 r--p 00000000 00:3e 1245856                    /usr/bin/cat 
555555556000-55555555b000 r-xp 00002000 00:3e 1245856                    /usr/bin/cat
55555555b000-55555555d000 r--p 00007000 00:3e 1245856                    /usr/bin/cat
55555555d000-55555555e000 r--p 00008000 00:3e 1245856                    /usr/bin/cat
55555555e000-55555555f000 rw-p 00009000 00:3e 1245856                    /usr/bin/cat
55555555f000-555555580000 rw-p 00000000 00:00 0 
7fffff58c000-7fffff5b0000 rw-p 00000000 00:00 0 
7fffff5b0000-7fffff5d8000 r--p 00000000 00:3e 1246610                    /usr/lib/x86_64-linux-gnu/libc.so.6
7fffff5d8000-7fffff761000 r-xp 00028000 00:3e 1246610                    /usr/lib/x86_64-linux-gnu/libc.so.6
7fffff761000-7fffff7b0000 r--p 001b1000 00:3e 1246610                    /usr/lib/x86_64-linux-gnu/libc.so.6
7fffff7b0000-7fffff7b4000 r--p 001ff000 00:3e 1246610                    /usr/lib/x86_64-linux-gnu/libc.so.6
7fffff7b4000-7fffff7b6000 rw-p 00203000 00:3e 1246610                    /usr/lib/x86_64-linux-gnu/libc.so.6
7fffff7b6000-7fffff7c3000 rw-p 00000000 00:00 0 
7fffff7c5000-7fffff7c6000 ---p 00000000 00:00 0 
7fffff7c6000-7ffffffc6000 rw-p 00000000 00:00 0 
7ffffffc6000-7ffffffc7000 r--p 00000000 00:3e 1246590                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2  
7ffffffc7000-7fffffff2000 r-xp 00001000 00:3e 1246590                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fffffff2000-7fffffffc000 r--p 0002c000 00:3e 1246590                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fffffffc000-7fffffffe000 r--p 00036000 00:3e 1246590                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fffffffe000-800000000000 rw-p 00038000 00:3e 1246590                    /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
800000000000-800000026000 r--p 00000000 00:35 2                          /run/rosetta/rosetta
800000026000-800000097000 r-xp 00026000 00:35 2                          /run/rosetta/rosetta
8000000a0000-8000001a6000 rw-p 000a0000 00:35 2                          /run/rosetta/rosetta
effff7dd0000-effff7de7000 rw-p 00000000 00:00 0 
effff7de7000-effff7de8000 ---p 00000000 00:00 0 
effff7de8000-effff7dec000 rw-p 00000000 00:00 0 
effff7dec000-effff7ded000 ---p 00000000 00:00 0 
effff7ded000-effff7ff8000 rw-p 00000000 00:00 0 
effff7ff8000-efffffff8000 rwxp 00000000 00:00 0 
efffffff8000-f00008a78000 rw-p 00000000 00:00 0 
ffffa458d000-ffffa458f000 r--p 00000000 00:00 0                          [vvar]
ffffa458f000-ffffa4590000 r-xp 00000000 00:00 0                          [vdso]
fffff660d000-fffff662e000 rw-p 00000000 00:00 0                          [stack]
```
