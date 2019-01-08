/*
 *  Copyright (c) 2014 Nuvoton Technology Corp.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/io.h>

#define REG_APLLCON	0xB0000220
#define REG_UPLLCON	0xB0000224
#define REG_MPLLCON	0xB0000228
#define REG_CLKDIV0	0xB000020C
#define REG_CLKDIV1	0xB0000210
#define REG_CLKDIV2	0xB0000214
#define REG_CLKDIV3	0xB0000218
#define REG_CLKDIV4	0xB000021C
#define REG_CLKDIV5	0xB0000238
#define REG_CLKDIV6	0xB000023C
#define REG_CLKDIV7	0xB0000240
#define REG_CLKDIV8	0xB0000244

static unsigned int calc_freq(unsigned int reg)
{
    unsigned int res;

    if (reg & (1<<14))
    {
	/* PLL in power-down mode */
	return 0;
    }
    if (reg & (1<<15))
    {
	/* PLL in bypass mode */
	return EXT_CLK;
    }
    /* input divisor */
    res = EXT_CLK/((reg & 0x780)>>7);
    /* feedback divisor */
    res = res * (reg & 0x7F);
    /* output divisor */
    reg = (reg >> 11) & 3;
    while (reg--)
    {
	res = res / 2;
    }
    return res;
}

static void print_clocks(void)
{
    unsigned int sys, cpu, hclk1, hclk234, pclk, reg;

    /* System clock */
    reg = readl(REG_CLKDIV0);
    switch ((reg>>3) & 3)
    {
	case 0:
	    sys = EXT_CLK;
	    break;
	case 1:
	    sys = calc_freq(readl(REG_MPLLCON));
	    break;
	case 2:
	    sys = calc_freq(readl(REG_APLLCON));
	    break;
	default:
	    sys = calc_freq(readl(REG_UPLLCON));
	    break;
    }
    sys = sys / ((reg & 7)+1);
    sys = sys / (((reg >> 8) & 0xF)+1);
    sys = sys / 1000000;

    reg = readl(REG_CLKDIV4);
    cpu = sys / ((reg & 0x0F)+1);
    if (cpu != sys)
    {
	hclk1 = cpu;
    }
    else
    {
	hclk1 = cpu / 2;
    }
    reg  = reg >> 4;
    hclk234 = (sys / 2) / ((reg & 0x0F)+1);
    reg = reg >> 4;
    if (reg & 0x0F)
    {
	pclk = hclk1 / ((reg & 0x07)+1);
    }
    else
    {
	pclk = hclk1 / 4;
    }

    printf("SYSCLK=%uMHz, CPUCLK=%uMHz, HCLK1=%uMHz, HCLK234=%uMHz, PCLK=%uMHz\n", sys, cpu, hclk1, hclk234, pclk);
}

int print_cpuinfo (void)
{

        printf("CPU: N3292X\n");
	print_clocks();
        return(0);
}

int arch_cpu_init(void)
{
        // do nothing...

        return 0;
}

