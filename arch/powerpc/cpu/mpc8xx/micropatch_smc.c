// SPDX-License-Identifier: GPL-2.0

/*
 * Microcode patches for the CPM as supplied by Motorola.
 */

#include <linux/string.h>
#include <linux/io.h>
#include <asm/immap_8xx.h>
#include <asm/cpm_8xx.h>

static uint patch_2000[] = {
	0x3fff0000, 0x3ffd0000, 0x3ffb0000, 0x3ff90000,
	0x5fefeff8, 0x5f91eff8, 0x3ff30000, 0x3ff10000,
	0x3a11e710, 0xedf0ccb9, 0xf318ed66, 0x7f0e5fe2,
	0x7fedbb38, 0x3afe7468, 0x7fedf4d8, 0x8ffbb92d,
	0xb83b77fd, 0xb0bb5eb9, 0xdfda7fed, 0x90bde74d,
	0x6f0dcbd3, 0xe7decfed, 0xcb50cfed, 0xcfeddf6d,
	0x914d4f74, 0x5eaedfcb, 0x9ee0e7df, 0xefbb6ffb,
	0xe7ef7f0e, 0x9ee57fed, 0xebb7effa, 0xeb30affb,
	0x7fea90b3, 0x7e0cf09f, 0xbffff318, 0x5fffdfff,
	0xac35efea, 0x7fce1fc1, 0xe2ff5fbd, 0xaffbe2ff,
	0x5fbfaffb, 0xf9a87d0f, 0xaef8770f, 0x7d0fb0a2,
	0xeffbbfff, 0xcfef5fba, 0x7d0fbfff, 0x5fba4cf8,
	0x7fddd09b, 0x49f847fd, 0x7efdf097, 0x7fedfffd,
	0x7dfdf093, 0xef7e7e1e, 0x5fba7f0e, 0x3a11e710,
	0xedf0cc87, 0xfb18ad0a, 0x1f85bbb8, 0x74283b7e,
	0x7375e4bb, 0x2ab64fb8, 0x5c7de4bb, 0x32fdffbf,
	0x5f0843f8, 0x7ce3e1bb, 0xe74f7ded, 0x6f0f4fe8,
	0xc7ba32be, 0x73f2efeb, 0x600b4f78, 0xe5bb760b,
	0x5388aef8, 0x4ef80b6a, 0xcfef9ee5, 0xabf8751f,
	0xefef5b88, 0x741f4fe8, 0x751e760d, 0x7fdb70dd,
	0x741cafce, 0xefcc7fce, 0x751e7088, 0x741ce7bb,
	0x334ecfed, 0xafdbefeb, 0xe5bb760b, 0x53ceaef8,
	0xafe8e7eb, 0x4bf8771e, 0x7e007fed, 0x4fcbe2cc,
	0x7fbc3085, 0x7b0f7a0f, 0x34b177fd, 0xb0e75e93,
	0xdf313e3b, 0xaf78741f, 0x741f30cc, 0xcfef5f08,
	0x741f3e88, 0xafb8771e, 0x5f437fed, 0x0bafe2cc,
	0x741ccfec, 0xe5ca53a9, 0x6fcb4f74, 0x5e89df27,
	0x2a923d14, 0x4b8fdf0c, 0x751f741c, 0x6c1eeffa,
	0xefea7fce, 0x6ffc309a, 0xefec3fca, 0x308fdf0a,
	0xadf85e7a, 0xaf7daefd, 0x5e7adf0a, 0x5e7aafdd,
	0x761f1088, 0x1e7c7efd, 0x3089fffe, 0x4908fb18,
	0x5fffdfff, 0xafbbf0f7, 0x4ef85f43, 0xadf81489,
	0x7a0f7089, 0xcfef5089, 0x7a0fdf0c, 0x5e7cafed,
	0xbc6e780f, 0xefef780f, 0xefef790f, 0xa7f85eeb,
	0xffef790f, 0xefef790f, 0x1489df0a, 0x5e7aadfd,
	0x5f09fffb, 0xe79aded9, 0xeff96079, 0x607ae79a,
	0xded8eff9, 0x60795edb, 0x607acfef, 0xefefefdf,
	0xefbfef7f, 0xeeffedff, 0xebffe7ff, 0xafefafdf,
	0xafbfaf7f, 0xaeffadff, 0xabffa7ff, 0x6fef6fdf,
	0x6fbf6f7f, 0x6eff6dff, 0x6bff67ff, 0x2fef2fdf,
	0x2fbf2f7f, 0x2eff2dff, 0x2bff27ff, 0x4e08fd1f,
	0xe5ff6e0f, 0xaff87eef, 0x7e0ffdef, 0xf11f6079,
	0xabf8f51e, 0x7e0af11c, 0x37cfae16, 0x7fec909a,
	0xadf8efdc, 0xcfeae52f, 0x7d0fe12b, 0xf11c6079,
	0x7e0a4df8, 0xcfea5ea0, 0x7d0befec, 0xcfea5ea2,
	0xe522efdc, 0x5ea2cfda, 0x4e08fd1f, 0x6e0faff8,
	0x7c1f761f, 0xfdeff91f, 0x6079abf8, 0x761cee00,
	0xf91f2bfb, 0xefefcfec, 0xf91f6079, 0x761c27fb,
	0xefdf5e83, 0xcfdc7fdd, 0x50f84bf8, 0x47fd7c1f,
	0x761ccfcf, 0x7eef7fed, 0x7dfd70ef, 0xef7e7f1e,
	0x771efb18, 0x6079e722, 0xe6bbe5bb, 0x2e66e5bb,
	0x600b2ee1, 0xe2bbe2bb, 0xe2bbe2bb, 0x2f5ee2bb,
	0xe2bb2ff9, 0x6079e2bb,
};

static uint patch_2f00[] = {
	0x30303030, 0x3e3e3030, 0xaf79b9b3, 0xbaa3b979,
	0x9693369f, 0x79f79777, 0x97333fff, 0xfb3b9e9f,
	0x79b91d11, 0x9e13f3ff, 0x3f9b6bd9, 0xe173d136,
	0x695669d1, 0x697b3daf, 0x79b93a3a, 0x3f979f91,
	0x379ff976, 0xf99777fd, 0x9779737d, 0xe9d6bbf9,
	0xbfffd9df, 0x97f7fd97, 0x6f7b9bff, 0xf9bd9683,
	0x397db973, 0xd97b3b9f, 0xd7f9f733, 0x9993bb9e,
	0xe1f9ef93, 0x73773337, 0xb936917d, 0x11f87379,
	0xb979d336, 0x8b7ded73, 0x1b7d9337, 0x31f3f22f,
	0x3f2327ee, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee,
	0xeeeeee4b, 0xf4fbdbd2, 0x58bb1878, 0x577fdfd2,
	0xd573b773, 0xf7374b4f, 0xbdbd25b8, 0xb177d2d1,
	0x7376856b, 0xbfdd687b, 0xdd2fff8f, 0x78ffff8f,
	0xf22f0000,
};

void cpm_load_patch(cpm8xx_t __iomem *cp)
{
	smc_uart_t __iomem *smp;

	out_be16(&cp->cp_rccr, 0);

	memcpy_toio(cp->cp_dpmem, patch_2000, sizeof(patch_2000));
	memcpy_toio(cp->cp_dpmem + 0xf00, patch_2f00, sizeof(patch_2f00));

	smp = (smc_uart_t __iomem *)&cp->cp_dpmem[PROFF_SMC1];
	out_be16(&smp->smc_rpbase, CONFIG_SMC1_RPBASE);
	smp = (smc_uart_t __iomem *)&cp->cp_dpmem[PROFF_SMC2];
	out_be16(&smp->smc_rpbase, CONFIG_SMC2_RPBASE);

	out_be16(&cp->cp_cpmcr1, 0x8080);
	out_be16(&cp->cp_cpmcr2, 0x8088);
	out_be16(&cp->cp_cpmcr3, 0);
	out_be16(&cp->cp_cpmcr4, 0);

	out_be16(&cp->cp_rccr, 2);
}