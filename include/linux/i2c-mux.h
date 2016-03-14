/*
 *
 * i2c-mux.h - functions for the i2c-bus mux support
 *
 * Copyright (c) 2008-2009 Rodolfo Giometti <giometti@linux.it>
 * Copyright (c) 2008-2009 Eurotech S.p.A. <info@eurotech.it>
 * Michael Lawnick <michael.lawnick.ext@nsn.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 */

#ifndef _LINUX_I2C_MUX_H
#define _LINUX_I2C_MUX_H

#ifdef __KERNEL__

struct i2c_mux_core {
	struct i2c_adapter *parent;
	struct i2c_adapter **adapter;
	int adapters;
	int max_adapters;
	struct device *dev;

	void *priv;

	int (*select)(struct i2c_mux_core *, u32 chan_id);
	int (*deselect)(struct i2c_mux_core *, u32 chan_id);
};

struct i2c_mux_core *i2c_mux_alloc(struct i2c_adapter *parent,
				   struct device *dev, int sizeof_priv,
				   u32 flags,
				   int (*select)(struct i2c_mux_core *, u32),
				   int (*deselect)(struct i2c_mux_core *, u32));

static inline void *i2c_mux_priv(struct i2c_mux_core *muxc)
{
	return muxc->priv;
}

int i2c_mux_reserve_adapters(struct i2c_mux_core *muxc, int adapters);

/*
 * Called to create a i2c bus on a multiplexed bus segment.
 * The chan_id parameter is passed to the select and deselect
 * callback functions to perform hardware-specific mux control.
 */
int i2c_mux_add_adapter(struct i2c_mux_core *muxc,
			u32 force_nr, u32 chan_id,
			unsigned int class);

/*
 * Allocate an i2c_mux_core and add one adapter with one call.
 */
struct i2c_mux_core *i2c_mux_one_adapter(struct i2c_adapter *parent,
					 struct device *dev, int sizeof_priv,
					 u32 flags, u32 force_nr,
					 u32 chan_id, unsigned int class,
					 int (*select)(struct i2c_mux_core *,
						       u32),
					 int (*deselect)(struct i2c_mux_core *,
							 u32));

void i2c_mux_del_adapters(struct i2c_mux_core *muxc);

#endif /* __KERNEL__ */

#endif /* _LINUX_I2C_MUX_H */
