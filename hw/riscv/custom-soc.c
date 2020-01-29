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
#include "hw/riscv/custom-finisher.h"
#include "hw/riscv/boot.h"
#include "chardev/char.h"
#include "exec/address-spaces.h"

static const struct MemmapEntry {
    hwaddr base;
    hwaddr size;
} rv_customsoc_memmap[] = {
    [RV_CUSTOMSOC_RAM]      = { 0x00000000,      0x400000 }, /*    4mb */

    [RV_CUSTOMSOC_UART0]    = { 0xF0000000,             0 }, /* puts   */
    [RV_CUSTOMSOC_FINISHER] = { 0xFFFFF000,             0 }, /* exit   */
};

static void riscv_custom_board_init(MachineState *machine)
{
    const struct MemmapEntry *memmap = rv_customsoc_memmap;

    RISCVCustomSOCState *s = g_new0(RISCVCustomSOCState, 1);
    MemoryRegion *system_memory = get_system_memory();
    MemoryRegion *ram = g_new(MemoryRegion, 1);
    unsigned int smp_cpus = machine->smp.cpus;

    /* Initialize SOC */
    object_initialize_child(OBJECT(machine), "soc", &s->soc, sizeof(s->soc),
                            TYPE_RISCV_HART_ARRAY, &error_abort, NULL);
    object_property_set_str(OBJECT(&s->soc), machine->cpu_type, "cpu-type",
                            &error_abort);
    object_property_set_int(OBJECT(&s->soc), smp_cpus, "num-harts",
                            &error_abort);
    object_property_set_bool(OBJECT(&s->soc), true, "realized",
                            &error_abort);

    /* register system memory */
    memory_region_init_ram(ram, NULL, "riscv_custom_board.ram",
                           memmap[RV_CUSTOMSOC_RAM].size, &error_fatal);
    memory_region_add_subregion(system_memory, memmap[RV_CUSTOMSOC_RAM].base,
        ram);

    if (machine->kernel_filename) {
        /*uint64_t kernel_entry =*/ riscv_load_kernel(machine->kernel_filename);

        if (machine->initrd_filename) {
	    /* ignored */
        }
    }

    /* MMIO */
    riscv_finisher_create(memmap[RV_CUSTOMSOC_FINISHER].base);

    serial_mm_init(system_memory, memmap[RV_CUSTOMSOC_UART0].base,
        0, NULL, 399193,
        serial_hd(0), DEVICE_LITTLE_ENDIAN);
}

static void riscv_custom_board_machine_init(MachineClass *mc)
{
    mc->desc = "RISC-V Custom Board (Privileged ISA v1.10)";
    mc->init = riscv_custom_board_init;
    mc->max_cpus = 1;
    mc->default_cpu_type = RV_CUSTOM_CPU;
}

DEFINE_MACHINE("rv-custom-soc", riscv_custom_board_machine_init)
