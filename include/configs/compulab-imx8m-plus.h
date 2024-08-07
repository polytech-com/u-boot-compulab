/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2021 CompuLab
 */

#ifndef __COMPULAB_IMX8M_PLUS
#define __COMPULAB_IMX8M_PLUS

#include <linux/sizes.h>
#include <asm/arch/imx-regs.h>

#include "imx_env.h"

#define CONFIG_SYS_BOOTM_LEN		(64 * SZ_1M)

#define CONFIG_SPL_MAX_SIZE		(152 * 1024)
#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_USE_SECTOR
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300
#define CONFIG_SYS_UBOOT_BASE	(QSPI0_AMBA_BASE + CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR * 512)

#define SPL_STACK_ADDR			0x96dff0
#define SHARED_DDR_INFO			SPL_STACK_ADDR
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SPL_STACK		SPL_STACK_ADDR
#define CONFIG_SPL_BSS_START_ADDR	0x96e000
#define CONFIG_SPL_BSS_MAX_SIZE		SZ_4K	/* 4 KB */
#define CONFIG_SYS_SPL_MALLOC_START	0x42200000
#define CONFIG_SYS_SPL_MALLOC_SIZE	SZ_256K	/* 256 KB */

/* For RAW image gives a error info not panic */
#define CONFIG_SPL_ABORT_ON_RAW_IMAGE

#endif

#define CONFIG_CMD_READ
#define CONFIG_SERIAL_TAG
#define CONFIG_FASTBOOT_USB_DEV 0

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_DISTRO_DEFAULTS
#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 2)

#include <config_distro_bootcmd.h>
#else
#define BOOTENV
#endif


#define JAILHOUSE_ENV \
	"jh_clk= \0 " \
	"jh_mmcboot=setenv fdtfile ucm-imx8m-plus-root.dtb;" \
		"setenv jh_clk clk_ignore_unused mem=2048MB; " \
			   "if run loadimage; then " \
				   "run mmcboot; " \
			   "else run jh_netboot; fi; \0" \
	"jh_netboot=setenv fdtfile ucm-imx8m-plus-root.dtb; setenv jh_clk clk_ignore_unused mem=2048MB; run netboot; \0 "

#define CONFIG_MFG_ENV_SETTINGS \
	CONFIG_MFG_ENV_SETTINGS_DEFAULT \
	"initrd_addr=0x43800000\0" \
	"initrd_high=0xffffffffffffffff\0" \
	"emmc_dev=2\0"\
	"sd_dev=1\0" \

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS		\
	CONFIG_MFG_ENV_SETTINGS \
	JAILHOUSE_ENV \
	BOOTENV \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0" \
	"stdin=serial,usbkbd\0" \
	"autoload=off\0" \
	"scriptaddr=0x43500000\0" \
	"kernel_addr_r=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"bsp_script=boot.scr\0" \
	"image=Image\0" \
	"splashimage=0x50000000\0" \
	"console=tty1 console=ttymxc1,115200\0" \
	"fdt_addr_r=0x43000000\0"			\
	"fdto_addr_r=0x43800000\0"			\
	"fdt_addr=0x43000000\0"			\
	"boot_fdt=try\0" \
	"fdt_high=0xffffffffffffffff\0"		\
	"boot_fit=yes\0" \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"bootm_size=0x10000000\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	"emmc_root=/dev/mmcblk2p2\0" \
	"boot_part=1\0" \
	"root_opt=rootwait rw\0" \
	"emmc_ul=setenv iface mmc; setenv dev ${emmc_dev}; setenv part ${boot_part};" \
		"setenv bootargs panic=5 console=${console} root=${emmc_root} ${root_opt} ${rauc_slot};\0" \
	"bootlist=rauc_ul emmc_ul\0" \
	"rauc_ul=test -n \"${BOOT_ORDER}\" || setenv BOOT_ORDER A B; " \
		"test -n \"${BOOT_A_LEFT}\" || setenv BOOT_A_LEFT 3; " \
		"test -n \"${BOOT_B_LEFT}\" || setenv BOOT_B_LEFT 3; " \
		"setenv rauc_slot; " \
		"for BOOT_SLOT in ${BOOT_ORDER}; do " \
			"if test -n \"${rauc_slot}\"; then " \
				"echo \"Skip remaining slots\"; " \
			"elif test \"${BOOT_SLOT}\" = \"A\"; then " \
				"if test ${BOOT_A_LEFT} -gt 0; then " \
					"setexpr BOOT_A_LEFT ${BOOT_A_LEFT} - 1; " \
					"echo \"Found valid RAUC slot A\"; " \
					"setenv rauc_slot \"rauc.slot=A\"; " \
					"setenv rauc_part 3;" \
					"setenv boot_part 1;" \
				"fi; " \
			"elif test \"${BOOT_SLOT}\" = \"B\"; then " \
				"if test ${BOOT_B_LEFT} -gt 0; then " \
					"setexpr BOOT_B_LEFT ${BOOT_B_LEFT} - 1; " \
					"echo \"Found valid RAUC slot B\"; " \
					"setenv rauc_slot \"rauc.slot=B\"; " \
					"setenv rauc_part 4;" \
					"setenv boot_part 2;" \
				"fi; " \
			"fi; " \
		"done; " \
		"if test -n \"${rauc_slot}\"; then " \
			"setenv emmc_root /dev/mmcblk2p${rauc_part}; " \
			"saveenv; " \
		"else " \
			"echo \"No valid RAUC slot found. Resetting tries to 3\"; " \
			"setenv BOOT_A_LEFT 3; " \
			"setenv BOOT_B_LEFT 3; " \
			"saveenv; " \
			"reset; " \
		"fi;\0" \
	"bsp_bootcmd=echo Running BSP bootcmd ...; " \
		"for src in ${bootlist}; do " \
			"run ${src}; " \
		"done; " \
		"part size mmc ${emmc_dev} ${boot_part} boot_part_block_size; " \
		"read mmc ${emmc_dev}:${boot_part} 0x48000000 0 0x${boot_part_block_size}; " \
		"bootm 0x48000000; "
#endif

/* Link Definitions */
#define CONFIG_SYS_INIT_RAM_ADDR	0x40000000
#define CONFIG_SYS_INIT_RAM_SIZE	0x80000
#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_ENV_OVERWRITE
#define CONFIG_MMCROOT			"/dev/mmcblk1p2"  /* USDHC2 */

/* Totally 6GB DDR */
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM			0x40000000
#define PHYS_SDRAM_SIZE			0x80000000	/* 2 GB */
#define PHYS_SDRAM_2			0x100000000
#define PHYS_SDRAM_2_SIZE		0x00000000	/* 0 GB */

#define MEMTEST_DIVIDER   2
#define MEMTEST_NUMERATOR 1

#define CONFIG_MXC_UART_BASE		UART2_BASE_ADDR

/* Monitor Command Prompt */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

#define CONFIG_IMX_BOOTAUX

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_FSL_ESDHC_ADDR	0

#ifdef CONFIG_NAND_MXS
#define CONFIG_CMD_NAND_TRIMFFS

/* NAND stuff */
#define CONFIG_SYS_MAX_NAND_DEVICE     1
#define CONFIG_SYS_NAND_BASE           0x20000000
#define CONFIG_SYS_NAND_5_ADDR_CYCLE
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_NAND_USE_FLASH_BBT
#endif /* CONFIG_NAND_MXS */

#define CONFIG_SYS_I2C_SPEED		100000

#define CONFIG_USB_MAX_CONTROLLER_COUNT         2
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_VBUS_DRAW 2

#ifdef CONFIG_SYS_PROMPT
#undef CONFIG_SYS_PROMPT
#endif
#define CONFIG_SYS_PROMPT CONFIG_SYS_BOARD"=> "
