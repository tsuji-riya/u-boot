// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 */

#include <dm.h>
#include <asm/io.h>
#include <asm/arch-rockchip/uart.h>
#include <led.h>

int board_early_init_r(void) {

        /* LED setup */
	//if (IS_ENABLED(CONFIG_LED))
		//led_default_state();

	return 0;

}

