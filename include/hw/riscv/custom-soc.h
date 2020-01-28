/*
 * QEMU RISC-V Custom Board
 *
 * Copyright (c) 2020 Jean-Francois Monestier
 *
 * github@monestier.me
 *
 * Simple RISC-V machine with 16550a UART
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_RISCV_CUSTOM_SOC_H
#define HW_RISCV_CUSTOM_SOC_H

#if defined(TARGET_RISCV32)
#define RV_CUSTOM_CPU TYPE_RISCV_CPU_CUSTOM32
#elif defined(TARGET_RISCV64)
#error Not supported - This custom SoC is 32b only - Please re-run "./configure --target-list=riscv32-softmmu"
#endif

#endif
