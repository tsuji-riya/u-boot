/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration for the MX10 style RK3229 TV box.
 *
 * Only the SD card (mmc0) and the eMMC (mmc2) are boot targets: the SDIO
 * slot (mmc1) carries the Wi-Fi module, and neither Ethernet (internal
 * RMII PHY) nor USB host are supported by U-Boot for this SoC yet.
 */
#ifndef __CONFIG_MX10_RK3229_H
#define __CONFIG_MX10_RK3229_H

#define BOOT_TARGETS	"mmc0 mmc2"

#include <configs/rk322x_common.h>

/*
 * Extra convenience command to start the kernel kept in the original
 * Rockchip "kernel" partition of the eMMC (sector 0x12000, 12 MiB, "KRNL"
 * wrapper = 8 byte header in front of the zImage).  Only useful with a
 * zImage that has its DTB appended (kernel-appended-dtb.img).
 */
#undef CFG_EXTRA_ENV_SETTINGS
#define CFG_EXTRA_ENV_SETTINGS \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"fdt_high=0x7fffffff\0" \
	"partitions=" PARTS_DEFAULT \
	ENV_MEM_LAYOUT_SETTINGS \
	"boot_targets=" BOOT_TARGETS "\0" \
	"boot_rkemmc=mmc dev 2 && mmc read ${kernel_addr_r} 0x12000 0x6000 && " \
		"setexpr rk_zimage ${kernel_addr_r} + 8 && bootz ${rk_zimage}\0"

#endif
