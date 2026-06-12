/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2026, schoosh212 <superaviation001@gmail.com>
 * Copyright (c) 2024, Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 * copyright (c) 2026, gunbileg naranbaatar <gunbileg2010@gmail.com>
 */
#include <board.h>
#include <drivers/framework.h>
#include <lib/simplefb.h>.
#include <soc/exynos3830.h>
#include <stdint.h>

int a145f_init(void)
{
	/* Kick the Exynos 850 Display Controller (DECON) hardware trigger to flush buffer */
	*(int*) (DECON_F_BASE + HW_SW_TRIG_CONTROL) = 0x1281;
	return 0;
}

#ifdef CONFIG_SIMPLE_FB
static struct video_info a145f_fb = {
	.format = FB_FORMAT_ARGB8888,
	.width = 1080,
	.height = 2408,
	.stride = 4,
	.address = (void *)0xfa000000 /* Exynos 850 default physical RAM framebuffer allocation region */
};
#endif

int a145f_drv(void)
{
#ifdef CONFIG_SIMPLE_FB
	REGISTER_DRIVER("simplefb", simplefb_probe, &a145f_fb);
#endif
	return 0;
}

struct board_data board_ops = {
	.name = "samsung-a145f",
	.ops = {
		.early_init = a145f_init,
		.drivers_init = a145f_drv,
	},
	.quirks = 0
};