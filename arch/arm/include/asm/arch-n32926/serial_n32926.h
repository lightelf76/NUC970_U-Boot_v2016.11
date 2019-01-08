/*
 * Copyright (c) 2012 Nuvoton Technology Corp.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Description:   N32926 UART register definition
 */
#ifndef _SERIAL_N32926_H
#define _SERIAL_N32926_H

/* Line control register bits */
#define WB_DATA_BITS_5    0x00
#define WB_DATA_BITS_6    0x01
#define WB_DATA_BITS_7    0x02
#define WB_DATA_BITS_8    0x03

#define WB_STOP_BITS_1    0x00
#define WB_STOP_BITS_2    0x04

#define WB_PARITY_NONE    0x00
#define WB_PARITY_ODD     0x00
#define WB_PARITY_EVEN    0x10


#define LEVEL_1_BYTE      0x00
#define LEVEL_4_BYTES     0x40
#define LEVEL_8_BYTES     0x80
#define LEVEL_14_BYTES    0xC0


#define TX_RX_FIFO_RESET    0x06
#define ENABLE_TIME_OUT     (0x80+0x20)
#define THR_EMPTY           0x20    // Transmit Holding Register Empty
#define RX_DATA_READY       0x01

/* FIFO status register bits */
#define RX_FIFO_EMPTY       0x4000
#define TX_FIFO_FULL        0x800000 

/* Baudrate divisor register bits */
#define BD_DIV_X_EN	0x20000000
#define BD_DIV_X_ONE	0x10000000
#define BD_DIV_X_MASK	0x0F000000

#define REG_COM_TX     (0x00)   /* (W) TX buffer */
#define REG_COM_RX     (0x00)   /* (R) RX buffer */
#define REG_COM_IER    (0x04)   /* Interrupt enable register */
#define REG_COM_FCR    (0x08)   /* FIFO control register */
#define REG_COM_LCR    (0x0C)   /* Line control register */
#define REG_COM_MCR    (0x10)   /* Modem control register */
#define REG_COM_MSR    (0x14)   /* Modem status register */
#define REG_COM_FSR    (0x18)   /* FIFO status register */
#define REG_COM_ISR    (0x1C)   /* Interrupt status register */
#define REG_COM_TOR    (0x20)   /* (R) Time out register */
#define REG_COM_BAUD   (0x24)   /* Baud rate divisor register */


#define REG_MFSEL      0xB0000080
#define UART0_BASE     0xB8008000
#define UART1_BASE     0xB8008100

#endif  // _SERIAL_N32926_H
