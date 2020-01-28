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

#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qemu/log.h"
#include "qemu/error-report.h"
#include "qapi/error.h"
#include "hw/hw.h"
#include "hw/boards.h"
#include "hw/loader.h"
#include "hw/sysbus.h"
#include "hw/char/serial.h"
#include "target/riscv/cpu.h"
#include "hw/riscv/riscv_hart.h"
#include "hw/riscv/custom-soc.h"
#include "hw/riscv/boot.h"
#include "chardev/char.h"
#include "exec/address-spaces.h"

static void riscv_custom_board_init(MachineState *machine)
{
}

static void riscv_custom_board_machine_init(MachineClass *mc)
{
    mc->desc = "RISC-V Custom Board (Privileged ISA v1.10)";
    mc->init = riscv_custom_board_init;
    mc->max_cpus = 1;
    mc->default_cpu_type = RV_CUSTOM_CPU;
}

DEFINE_MACHINE("rv-custom-soc", riscv_custom_board_machine_init)
