/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __DDR_H__
#define __DDR_H__

#ifdef CONFIG_SPL_BUILD
extern struct dram_timing_info ucm_dram_timing_01061010;
extern struct dram_timing_info ucm_dram_timing_ff000010;
extern struct dram_timing_info ucm_dram_timing_ff060018;
#endif

void spl_dram_init(void);

struct lpddr4_tcm_desc {
	unsigned int size;
	unsigned int sign;
	unsigned int index;
	unsigned int count;
};

struct lpddr4_desc {
	char name[16];
	unsigned int id;
	unsigned int size;
	unsigned int count;
	/* an optional field
	 * use it if default is not the
	 * 1-st array entry */
	unsigned int _default;
	/* An optional field to distiguish DRAM chips that
	 * have different geometry, though return the same MRR.
	 * Default value 0xff
	 */
	u8	subind;
	struct dram_timing_info *timing;
	char *desc[4];
};

static const struct lpddr4_desc lpddr4_array[] = {
	{ .name = "Samsung",	.id = 0xDEADBEEF, .subind = 0xff, .size = 2048, .count = 1,
#ifdef CONFIG_SPL_BUILD
		.timing = &ucm_dram_timing_01061010
#endif
	},
	{ .name = "Samsung",	.id = 0x01061010, .subind = 0xff, .size = 2048, .count = 1,
#ifdef CONFIG_SPL_BUILD
		.timing = &ucm_dram_timing_01061010
#endif
	},
	{ .name = "Micron",	.id = 0xff000010, .subind = 0xff, .size = 4096, .count = 1,
#ifdef CONFIG_SPL_BUILD
		.timing = &ucm_dram_timing_ff000010
#endif
	},
	{ .name = "Kingston",	.id = 0xff060018, .subind = 0xff, .size = 8192, .count = 1,
#ifdef CONFIG_SPL_BUILD
		.timing = &ucm_dram_timing_ff060018
#endif
	},
};

unsigned int lpddr4_get_mr(void);
const struct lpddr4_desc *lpddr4_get_desc_by_id(unsigned int id);
size_t lppdr4_get_ramsize(void);
#endif