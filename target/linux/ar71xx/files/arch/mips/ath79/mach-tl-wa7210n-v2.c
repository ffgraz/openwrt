/*
 *  TP-LINK TL-WA7210N v2.1 board support
 *
 *  Copyright (C) 2011 dongyuqi <729650915@qq.com>
 *  Copyright (C) 2011-2012 Gabor Juhos <juhosg@openwrt.org>
 *  Copyright (C) 2014 Nicolas Braud-Santoni <nicolas@braud-santoni.eu>
 *  Copyright (C) 2014 Alexander List <alex@graz.funkfeuer.at>
 *  rebased on TL-WA7510Nv1 support,
 *    Copyright (C) 2012 Stefan Helmert <helst_listen@aol.de>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/platform_device.h>

#include <asm/mach-ath79/ar71xx_regs.h>
#include <asm/mach-ath79/ath79.h>

#include "dev-dsa.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "machtypes.h"
#include "pci.h"

#include "common.h"


static const char *tl_wa7210n_v2_part_probes[] = {
        "tp-link",
        NULL,
};

static struct flash_platform_data tl_wa7210n_v2_flash_data = {
        .part_probes    = tl_wa7210n_v2_part_probes,
};

static void __init tl_wa7210n_v2_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);


	/* use this to switch off LAN-LED */
/*        ath79_gpio_function_disable(AR724X_GPIO_FUNC_ETH_SWITCH_LED0_EN |
                                    AR724X_GPIO_FUNC_ETH_SWITCH_LED1_EN |
                                    AR724X_GPIO_FUNC_ETH_SWITCH_LED2_EN |
                                    AR724X_GPIO_FUNC_ETH_SWITCH_LED3_EN |
                                    AR724X_GPIO_FUNC_ETH_SWITCH_LED4_EN);
*/
        /*
         * ath79_eth0 would be the WAN port, but is not connected on
         * the TL-WA7510N like the TL-WA901ND. ath79_eth1 connects to the internal switch chip,
         * however we have a single LAN port only.
         */
        ath79_init_mac(ath79_eth1_data.mac_addr, mac, 0);
        ath79_register_mdio(0, 0x0);
        ath79_register_eth(1);

	ath79_register_m25p80(&tl_wa7210n_v2_flash_data);

	ath79_register_pci();
}

MIPS_MACHINE(ATH79_MACH_TL_WA7210N_V2, "TL-WA7210N-v2", "TP-LINK TL-WA7210N v2",
	     tl_wa7210n_v2_setup);
