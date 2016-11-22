#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x103ef23b, "module_layout" },
	{ 0x1678a900, "elv_unregister" },
	{ 0x781cacfe, "elv_register" },
	{ 0x37a0cba, "kfree" },
	{ 0x5df0d2b7, "elv_dispatch_sort" },
	{ 0x50eedeb8, "printk" },
	{ 0x1272ff5e, "kmem_cache_alloc" },
	{ 0xc86dd457, "kmalloc_caches" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F1431C52920D0B76A249CF2");
