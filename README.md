# Linux-System-programming
Linux Device Drivers 

## Dependencies should be installed first 

```c

sudo apt-get update
sudo apt-get install build-essential lzop u-boot-tools net-tools bison flex libssl-dev libncurses5-dev libncursesw5-dev unzip chrpath xz-utils minicom wget git-core
```

## Download the linux kernel from the following URL:
```c
https://github.com/raspberrypi/linux
```

## Download the toolchain from the following URL:
```c
https://snapshots.linaro.org/gnu-toolchain/14.0-2023.06-1/arm-linux-gnueabihf/
```

## Linux Kernel Modules (LKMs)
# Static (y)
When you build a linux kernel, you can make your module statically linked to the kernel image (module becomes part of the final linux kernel image).
this methode increases the size of the final linux kernel image.
Since the module is built in into the linux kernel image, you can not unload the module.
It occupies the memory permanently during run time.
# Dynamic (m)
When you build a linux kernel, these modules are not built into the final kernel image, and rather there are compiled and linked separately to produce .ko files.
You can dynamically load and unload these modules from the kernel using user space programs such as (insmod, modprob, rmmod).


## Function Section attributes
```c
__init  // >> #define __init        __section(.init.text)
        // >> #define __initdata    __section(.init.data)
        // >> #define __initconst   __section(.init.rodata)  
        // All of these are compiler directives, which direct the compiler to keep data or code in an output section called ".init"

__exit // >> #define __exit         __section(.exit.text)
       // this is compiler directive, which directs the compiler to keep data or code in an output section called ".exit"
```
__init & __exit makes sense only for static modules (built-in modules).
specially __exit, you know that for built in modules clean-up function is not required.
So, when you use the __exit macro with a clean-up function, the kernel build system will exclude those functions during thr build process itself.

## Module entry point registration
```c
module_init(my_kernel_module_init);
module_exit(my_kernel_module_exit);
```
These are the macros used to register your module's init function and clean-up function with the kernel,
Here module_init/module_exit is not a function, but a macro defined in linux/module.h .
For example, module_init() will add its parameter to the init entry point database of the kernel.
module_exit() will add its parameter to exit entry point database of the kernel.

## Module description
```c
// this is descriptive information about the module
MODULE_LICENSE("GPL");
MODULE_AUTHOR("www.LKM-Author.com");    // the Author of the kernel module 
MODULE_DESCRIPTION("A Kernel module to print hello message");
```
## MODULE_INFO
```c
MODULE_INFO(name , "string_value");
MODULE_INFO(board , "Raspberry pi");
```
You can see the module information by running the following command on the .ko file.
```c
aarch64-linux-gnu-objdump -d-j .modinfo helloworld.ko
```

## Building a Kernel Module
Kernel module can be built in 2 ways 
        1 - Statically linked against the kernel image
        2 - Dynamically loadable 
### Dynamically loadable kernel module
there are two types:
        1 - In tree module (internal to the linux kernel tree)
        2 - Out of tree module(external to the linux kernel tree)

## build first LKM for our host machine:
first you need to know the kernel version
```c
uname -r
        // you will get something like the following 
        // 6.8.0-87-generic
```
### create simple make file 
```c
obj-m := main.o
```
now run the following
```c
make -C /lib/modules/6.8.0-87-generic/build/ M=$PWD modules
```
the main.ko file should be created now
