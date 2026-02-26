// SPDX-License-Identifier: GPL-2.0+
/*
 * Board common code for CNC1800L
 *
 * Copyright (C) 2026 Cavium Inc.
 */

#include <asm/global_data.h>
#include <fdtdec.h>
#include <init.h>
#include <linux/types.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * DRAM configuration using device tree
 */

int dram_init(void) { return fdtdec_setup_mem_size_base(); }

int dram_init_banksize(void) { return fdtdec_setup_memory_banksize(); }

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo(void) {
  printf("CPU:   Cavium Celestial CNC1800L (ARM1176)\n");
  return 0;
}
#endif
