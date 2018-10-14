/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_floor_ceil.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:49:40 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:49:57 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		draw_wall(t_mlx *iw, int rx, int ry, t_draw2 *d)
{
	t_tex tex;

	if (rx == iw->p.x && ry == iw->p.y)
		return (0);
	d->nx = WINDOW_Y * 120 / ((int)(sqrt(pow(rx - iw->p.x, 2) +
					pow(ry - iw->p.y, 2))) + 1);
	d->tmp = d->nx;
	d->ny = (WINDOW_Y - d->nx) / 2;
	d->tmp3 = d->ny;
	d->nx += d->ny;
	if (d->ny < 0)
	{
		d->ny = 0;
		d->nx = WINDOW_Y;
	}
	d->tmp2 = (d->last_changed == 0) ? rx : ry;
	tex = get_tex(iw, d);
	d->tmp2 = (d->tmp2 % BSZ) * tex.w / BSZ;
	while (++d->ny < d->nx)
		pixel_put_img(iw, d->i, d->ny, (*((int *)tex.data + d->tmp2
			+ tex.w * ((d->ny - d->tmp3) * tex.h / d->tmp))));
	return (1);
}

void	draw_floor_ceil(t_mlx *iw, int rx, int ry, t_draw2 *d)
{
	float weight;

	d->tmp9 = sqrtf(pow((float)iw->p.x - (float)rx, 2) +
			pow((float)iw->p.y - (float)ry, 2)) + 0.000001;
	d->tmp = d->ny;
	while (++d->tmp < WINDOW_Y)
	{
		d->tmp4 = WINDOW_Y / (2.0 * (d->tmp) - WINDOW_Y);
		weight = d->tmp4 / d->tmp9;
		d->tmp5 = weight * (float)rx + (1.0 - weight) * (float)iw->p.x;
		d->tmp6 = weight * (float)ry + (1.0 - weight) * (float)iw->p.y;
		d->nx = (int)(d->tmp5 * (float)iw->t.floor.w + (float)(iw->p.x % BSZ) *
			(float)iw->t.floor.w / (float)BSZ) % iw->t.floor.w;
		d->ny = (int)(d->tmp6 * (float)iw->t.floor.h + (float)(iw->p.y % BSZ) *
			(float)iw->t.floor.h / (float)BSZ) % iw->t.floor.h;
		pixel_put_img(iw, d->i, d->tmp, *((int *)iw->t.floor.data +
					d->nx + iw->t.floor.w * d->ny));
		pixel_put_img(iw, d->i, abs(d->tmp - WINDOW_Y),
				*((int *)iw->t.ceil.data + d->nx + iw->t.ceil.w * d->ny));
	}
}

t_tex	get_tex(t_mlx *iw, t_draw2 *d)
{
	t_tex tex;

	if (iw->v.text_fill == 0)
	{
		if (d->last_changed == 0)
		{
			if (d->ydir == 1)
				tex = iw->t.t1;
			else
				tex = iw->t.t2;
		}
		else
		{
			if (d->xdir == 1)
				tex = iw->t.t3;
			else
				tex = iw->t.t4;
		}
	}
	else
		tex = iw->t.t1;
	return (tex);
}
