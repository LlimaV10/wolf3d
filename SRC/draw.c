/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:50:53 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:51:08 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	draw2(t_draw2 *d, t_mlx *iw)
{
	d->els = 0;
	d->rx = iw->p.x;
	d->ry = iw->p.y;
	d->ang = iw->p.rot - iw->p.angle +
		((float)d->i / (float)WINDOW_X * 2 * iw->p.angle);
	get_dir(d);
	d->k = get_k(d->ang);
	d->k = tan(d->k * 0.0174533);
	d->bb = (float)d->ry - d->k * (float)d->rx;
}

void	draw3(t_draw2 *d, t_mlx *iw)
{
	if (d->rx % BSZ == 0 && d->ry % BSZ == 0 && d->prev_last != 2)
		d->last_changed = d->prev_last;
	else
		d->prev_last = d->last_changed;
	if (draw_wall(iw, d->rx, d->ry, d) == 0)
		return ;
	draw_floor_ceil(iw, d->rx, d->ry, d);
	d->add_el.k = atan(d->k);
	d->add_el.b = d->bb;
	add_enemies(d, iw);
	draw_elements(iw, d, d->rx, d->ry);
	free_elements(d->els);
}

void	draw_try_add_el(t_draw2 *d, t_mlx *iw)
{
	if (d->b != '.' && d->b != 's')
	{
		d->add_el.rx = d->rx;
		d->add_el.ry = d->ry;
		d->add_el.k = d->k;
		d->add_el.b = d->bb;
		add_element(&(d->els), d, iw);
	}
	d->ny = ((d->ry + ((d->ydir == 0) ? -1 : 0)) / BSZ + d->ydir) * BSZ;
	d->nx = (int)roundf(((float)d->ny - d->bb) / (d->k + 0.000001));
}

void	draw(t_mlx *iw)
{
	t_draw2 d;

	d.i = iw->st - 1;
	d.prev_last = 2;
	while (++d.i < iw->end)
	{
		draw2(&d, iw);
		while ((d.b = iw->m.map[(d.ry + ((d.ydir == 0) ? -1 : 0)) / BSZ]
			[(d.rx + ((d.xdir == 0) ? -1 : 0)) / BSZ]) != '#')
		{
			draw_try_add_el(&d, iw);
			if (d.ny != d.ry && abs(d.nx - d.rx) <= abs(d.rx -
				((d.rx + ((d.xdir == 0) ? -1 : 0)) / BSZ + d.xdir) * BSZ))
			{
				d.last_changed = 0;
				d.rx = d.nx;
				d.ry = d.ny;
				continue ;
			}
			d.rx = ((d.rx + ((d.xdir == 0) ? -1 : 0)) / BSZ + d.xdir) * BSZ;
			d.ry = (int)roundf(d.k * (float)d.rx + d.bb);
			d.last_changed = 1;
		}
		draw3(&d, iw);
	}
}

void	threads_draw(t_mlx *iw)
{
	pthread_t	threads[THREADS];
	t_mlx		iws[THREADS];
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < THREADS)
	{
		iws[i] = *iw;
		iws[i].st = j;
		j += WINDOW_X / THREADS;
		iws[i].end = j;
		pthread_create(&threads[i], NULL,
				(void *(*)(void *))draw, (void *)&iws[i]);
	}
	while (i-- > 0)
		iw->status = pthread_join(threads[i], (void **)&iws[i]);
}
