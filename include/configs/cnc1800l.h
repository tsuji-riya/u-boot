/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration for Cavium CNC1800L
 *
 * Ported from u-boot-dsm232-2011 include/configs/cnc1800l.h
 */

#ifndef __CNC1800L_CONFIG_H
#define __CNC1800L_CONFIG_H

/* DRAM */
#define CONFIG_SYS_SDRAM_BASE 0x00000000

/* Unused but necessary to build arm1176 start.S */
#define CFG_SYS_UBOOT_BASE CONFIG_TEXT_BASE

/* Environment */
#define CONFIG_EXTRA_ENV_SETTINGS                                              \
  "bootargs=console=ttyS0,115200n8\0"                                          \
  "bootcmd=nand read 0x800000 0x200000 0x500000; bootm 0x800000\0"

#endif /* __CNC1800L_CONFIG_H */
