# CLI tools

## inode

```
open -> fd (int)
fd: 0,1,2 (stdin,stdout,stderr)
close(fd) (else resource-leak)
```

```
fd -> file | ...
...        | rm file
...        |
close(fd)  | ...
```

fd:
* files on disk
  - inode (index node): path, type, permissions, owner, ...
* socket
* inter-process communication

## `ls -alh`, `chmod`, `umask`

Permissions:
* Read
* Write
* eXecute (for directories: list directory contents)

For:
* Owner
* Group
* Users

## absolute vs relative path
