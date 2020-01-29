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

#ifndef HW_RISCV_FINISHER_H
#define HW_RISCV_FINISHER_H

#define TYPE_FINISHER "riscv.finisher"

#define FINISHER(obj) \
    OBJECT_CHECK(FinisherState, (obj), TYPE_FINISHER)

typedef struct FinisherState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    MemoryRegion mmio;
} FinisherState;

DeviceState *riscv_finisher_create(hwaddr addr);

#endif
