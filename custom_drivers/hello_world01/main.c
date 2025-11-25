#include<linux/module.h>

/* this is module initialization entry point */
static int __init hello_init(void)
{
    pr_info("ATON says: Hello World!\n");
    return 0;
}

/* this is module clean-up entry point */
static void __exit hello_exit(void)
{
    pr_info("ATON says: Goodbye World!\n");
}

/* this is registration of above entry points with kernel*/
module_init(hello_init);
module_exit(hello_exit);

/*this is descriptive information about the module*/
MODULE_LICENSE("GPL");  // this is module adhers to GPL license
MODULE_AUTHOR("ATON");
MODULE_DESCRIPTION("A simple Hello World Linux module.");
MODULE_VERSION("1.0");
MODULE_INFO(board , "Raspberry Pi 3 ");
