
#ifdef CONFIG_PLATFORM_DEV
struct platform_device  s3c_palt_dev = {
	.name		= "palt_dev",
	.id		= -1,
}
#endif

static struct platform_device *smdk4x12_devices[] __initdata = {
……
	#ifdef CONFIG_PLATFORM_DEV
        &s3c_palt_dev,
    #endif

};

config PLATFORM_DEV
		tristate "Enable platform dev config"
		default y
		help
		  Enable platform dev config



tftp -g -r platform_module.ko 192.168.1.101
