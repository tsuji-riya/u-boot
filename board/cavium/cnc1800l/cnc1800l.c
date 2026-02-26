// SPDX-License-Identifier: GPL-2.0+
/*
 * Board init for Cavium CNC1800L
 *
 * Ported from u-boot-dsm232-2011 board/cavium/cnc1800l/cnc1800l.c
 * Copyright (C) 2011 Cavium Inc.
 */

#include <asm/cache.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <cpu_func.h>
#include <init.h>
#include <linux/types.h>

DECLARE_GLOBAL_DATA_PTR;

/* Pinmux registers */
#define PINMUX_BASE 0xb2110000
#define PINMUX_I2C_ENABLE (PINMUX_BASE + 0x04)
#define PINMUX_UART_ENABLE (PINMUX_BASE + 0x08)
#define PINMUX_SPI_ENABLE (PINMUX_BASE + 0x0c)
#define PINMUX_SMI_ENABLE (PINMUX_BASE + 0x10)
#define PINMUX_DISPLAY_ENABLE (PINMUX_BASE + 0x14)
#define PINMUX_ETHER_ENABLE (PINMUX_BASE + 0x20)

/* NAND SMC controller base */
#define SMC_BASE 0x80100000

/* CE config register offsets */
#define CE0_CFG_0 (SMC_BASE + 0x00)
#define CE1_CFG_0 (SMC_BASE + 0x0c)
#define CE2_CFG_0 (SMC_BASE + 0x18)

#define CE0_CFG_1 (SMC_BASE + 0x04)
#define CE1_CFG_1 (SMC_BASE + 0x10)
#define CE2_CFG_1 (SMC_BASE + 0x1c)

#define CE0_CFG_2 (SMC_BASE + 0x08)
#define CE1_CFG_2 (SMC_BASE + 0x14)
#define CE2_CFG_2 (SMC_BASE + 0x20)

/* NAND timing parameters */
#define CS0_RWLENGTH 0x04
#define CS0_CE_SETUP 0x00
#define CS0_CE_HOLD 0x04
#define CS0_OE_SETUP 0x01
#define CS0_OE_HOLD 0x04
#define CS0_WE_SETUP 0x01
#define CS0_WE_HOLD 0x04
#define CS0_BE_SETUP 0x01
#define CS0_BE_HOLD 0x04

static void nand_smc_init(void) {
  u32 val;

  /* Configure read/write length for CE0/1/2 */
  val = (readl(CE0_CFG_0) & ~0x10000ff) | CS0_RWLENGTH;
  writel(val, CE0_CFG_0);
  writel(val, CE1_CFG_0);
  writel(val, CE2_CFG_0);

  /* Configure OE and CE timing */
  val = (CS0_OE_HOLD << 24) | (CS0_OE_SETUP << 16) | (CS0_CE_HOLD << 8) |
        CS0_CE_SETUP;
  writel(val, CE0_CFG_1);
  writel(val, CE1_CFG_1);
  writel(val, CE2_CFG_1);

  /* Configure BE and WE timing */
  val = (CS0_BE_HOLD << 24) | (CS0_BE_SETUP << 16) | (CS0_WE_HOLD << 8) |
        CS0_WE_SETUP;
  writel(val, CE0_CFG_2);
  writel(val, CE1_CFG_2);
  writel(val, CE2_CFG_2);
}

static void pinmux_init(void) {
  writel(0x1, PINMUX_I2C_ENABLE);     /* I2C0 enable */
  writel(0x1, PINMUX_UART_ENABLE);    /* UART0 enable */
  writel(0x1, PINMUX_SMI_ENABLE);     /* Smart card enable */
  writel(0x0, PINMUX_DISPLAY_ENABLE); /* Display default */
  writel(0x0, PINMUX_ETHER_ENABLE);   /* Ethernet enable */
}

int board_init(void) {
  icache_enable();
  pinmux_init();
  nand_smc_init();

  return 0;
}
