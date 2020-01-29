/*
 * QEMU Finisher
 *
 * Copyright (c) 2020 Jean-Francois Monestier
 *
 * github@monestier.me
 *
 * Terminate Execution
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
#include "hw/boards.h"
#include "hw/sysbus.h"
#include "qemu/module.h"
#include "sysemu/cpus.h"
#include "target/riscv/cpu.h"
#include "hw/riscv/custom-finisher.h"

static uint64_t riscv_finisher_read(void *opaque, hwaddr addr, unsigned int size)
{
    return 0;
}

static void riscv_finisher_write(void *opaque, hwaddr addr,
           uint64_t val64, unsigned int size)
{
    if (use_icount) {
        printf("\nRetired %" PRId64 " inst.\n", cpu_get_icount_raw());
    }

    switch(addr) {
	default:
        case 0:
            /* exit */
            exit((int)val64);
            break;
        case 4:
            /* abort */
            hw_error("%s: write: addr=0x%x val=0x%016" PRIx64 "\n",
                __func__, (int)addr, val64);
            break;
    }

    /* does not return */
}

static const MemoryRegionOps riscv_finisher_ops = {
    .read = riscv_finisher_read,
    .write = riscv_finisher_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4
    }
};

static void riscv_finisher_init(Object *obj)
{
    FinisherState *s = FINISHER(obj);

    memory_region_init_io(&s->mmio, obj, &riscv_finisher_ops, s,
                          TYPE_FINISHER, 0x1000);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static const TypeInfo riscv_finisher_info = {
    .name          = TYPE_FINISHER,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(FinisherState),
    .instance_init = riscv_finisher_init,
};

static void riscv_finisher_register_types(void)
{
    type_register_static(&riscv_finisher_info);
}

type_init(riscv_finisher_register_types)


/*
 * Create Finisher Device.
 */
DeviceState *riscv_finisher_create(hwaddr addr)
{
    DeviceState *dev = qdev_create(NULL, TYPE_FINISHER);
    qdev_init_nofail(dev);
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, addr);
    return dev;
}
