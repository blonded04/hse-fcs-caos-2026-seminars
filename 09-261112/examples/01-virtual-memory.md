# virtual memory

virtual memory - function: [0, 2^64 - 1] -> M

why it's nice to have virtual memory:
* addressing more than RAM is possible
* security reasons
* memory defragmention

OS page (4KB):
```
RAM (1GB)
|_4KB_|_4KB_|_4KB_|_____|_____|_____|..._____|_____|_____|
|_4KB_|                 |_4KB_|

|_____|_x___|_x___|_x___|
|_y___|_x___|_x___|_x___|
|_y___|_____|_z___|_____|
```

1. `inc (0x55...42)`
2. cpu goes to memory-management unit
3. TLB: virtual adress -> physical address
4. if page-fault mmu searches for page in RAM (minor page-fault)
5. if ram has no page, mmu searches for on disk (major paje-fault)
6. if disk has no page, mmu initiates `SIGSEGV`
