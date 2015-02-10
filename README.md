# kcatos
kcatos is an operating system from scratch.


## Requirements
* gcc
* multilib for gcc -m 32

## Build
```
make
```
## Launch
```
qemu-system-i386 -kernel KCat.Os
```

## Iso
```
make iso
```

## Live iso
```
make iso
sudo dd if=./KCat.Os.iso of=/dev/sdX ; sync
```
