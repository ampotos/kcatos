# kcatos
kcatos is an operating system from scratch.


## Requirements
* gcc
* multilib for gcc -m 32
* grub-mkrescue
* xorriso

## Build
```
make
```
## Launch
```
make run
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
