/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:48:21 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:48:30 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	get_dir(t_draw2 *d)
{
	if ((d->ang > 0 && d->ang < 180) || (d->ang > 360))
		d->xdir = 1;
	else
		d->xdir = 0;
	if ((d->ang > 90 && d->ang < 270) || (d->ang > 450))
		d->ydir = 1;
	else
		d->ydir = 0;
}

float	get_k(float ang)
{
	float	k;

	if (ang < 90)
		k = 90 + ang;
	else if (ang < 180)
		k = ang - 90;
	else if (ang < 270)
		k = ang - 90;
	else
		k = ang - 270;
	return (k);
}

t_draw2	get_start_d(t_mlx *iw, int i, float ang)
{
	t_draw2 d;

	d.rx = iw->p.x;
	d.ry = iw->p.y;
	d.els = 0;
	if (i != -1)
		d.ang = iw->p.rot - iw->p.angle +
			((float)i / (float)WINDOW_X * 2 * iw->p.angle);
	else
		d.ang = ang;
	get_dir(&d);
	d.k = get_k(d.ang);
	d.k = tan(d.k * 0.0174533) + 0.000001;
	d.bb = (float)d.ry - d.k * (float)d.rx;
	return (d);
}

void	get_r(t_mlx *iw, int i, t_get_ray *r, t_draw2 *d)
{
	r->dist = (int)sqrtf(pow(iw->p.x - d->rx, 2) + pow(iw->p.y - d->ry, 2));
	r->type = d->b;
	r->k = atan(d->k);
	if (i != -1)
	{
		r->rx = (d->rx + ((d->xdir == 0) ? -1 : 0)) / BSZ;
		r->ry = (d->ry + ((d->ydir == 0) ? -1 : 0)) / BSZ;
	}
	else
	{
		r->rx = d->rx;
		r->ry = d->ry;
	}
}

void	get_ray(t_mlx *iw, int i, t_get_ray *r, float ang)
{
	t_draw2 d;

	d = get_start_d(iw, i, ang);
	while ((d.b = iw->m.map[(d.ry + ((d.ydir == 0) ? -1 : 0)) / BSZ]
		[(d.rx + ((d.xdir == 0) ? -1 : 0)) / BSZ]) == '.' || d.b == 's')
	{
		d.ny = ((d.ry + ((d.ydir == 0) ? -1 : 0)) / BSZ + d.ydir) * BSZ;
		d.nx = (int)roundf(((float)d.ny - d.bb) / d.k);
		if (d.ny != d.ry && abs(d.nx - d.rx) <= abs(d.rx - ((d.rx +
			((d.xdir == 0) ? -1 : 0)) / BSZ + d.xdir) * BSZ))
		{
			d.rx = d.nx;
			d.ry = d.ny;
			continue ;
		}
		d.nx = ((d.rx + ((d.xdir == 0) ? -1 : 0)) / BSZ + d.xdir) * BSZ;
		d.ny = (int)roundf(d.k * (float)d.nx + d.bb);
		d.rx = d.nx;
		d.ry = d.ny;
	}
	get_r(iw, i, r, &d);
}
