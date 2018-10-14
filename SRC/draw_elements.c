/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:00:25 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:00:31 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	draw_el(t_mlx *iw, t_draw2 *d, t_element *(*el), t_tex tex)
{
	if ((d->tmp2 < 0 || d->tmp2 >= tex.w) ||
		(abs((*el)->rx - iw->p.x) < BSZ - 40
		&& abs((*el)->ry - iw->p.y) < BSZ - 40))
	{
		(*el) = (*el)->next;
		return ;
	}
	d->nx = WINDOW_Y * 120 / ((int)(sqrt(pow((*el)->rx -
		iw->p.x, 2) + pow((*el)->ry - iw->p.y, 2))) + 1);
	d->tmp = d->nx;
	d->ny = (WINDOW_Y - d->nx) / 2;
	d->tmp3 = d->ny;
	d->nx += d->ny;
	if (d->ny < 0)
	{
		d->ny = 0;
		d->nx = WINDOW_Y;
	}
	while (++d->ny < d->nx)
		pixel_put_img(iw, d->i, d->ny, (*((int *)tex.data + d->tmp2
			+ tex.w * ((d->ny - d->tmp3) * tex.h / d->tmp))));
	(*el) = (*el)->next;
}

void	draw_elements(t_mlx *iw, t_draw2 *d, int rx, int ry)
{
	t_element	*el;
	t_tex		tex;
	int			pl;

	el = d->els;
	while (el != 0)
	{
		if (el->type == 'e')
		{
			el->a.rot = get_enemy_rot(iw, el->a.e);
			get_min_max_enemy_rot(iw, &(el->a), iw->p.angle);
			if (el->a.rot > el->a.minrot &&
				el->a.rot < el->a.maxrot &&
				el->a.len < (int)sqrtf(pow(iw->p.x - rx, 2) +
					pow(iw->p.y - ry, 2)) && el->a.len > 50)
				draw_enemy(iw, &(el->a), d->i);
			el = el->next;
			continue ;
		}
		pl = draw_el_get_pl(iw, el, &tex);
		d->tmp2 = (el->last_changed == 0) ? el->rx : el->ry;
		d->tmp2 = (d->tmp2 % BSZ) * tex.w / BSZ + pl;
		draw_el(iw, d, &el, tex);
	}
}

void	draw_enemy(t_mlx *iw, t_add_enemy *a, int x)
{
	int i;
	int tmp;
	int tmp3;
	int color;

	if (a->e != 0)
	{
		i = WINDOW_Y / 2 - a->size / 2;
		tmp = i;
		tmp3 = WINDOW_Y / 2 + a->size / 2;
		while (++i < tmp3)
		{
			color = *((int *)iw->t.enemy[a->e->status].data +
				(iw->t.enemy[a->e->status].w / 2 + (int)a->delta
				* iw->t.enemy[a->e->status].w / (a->size / 2)) +
				iw->t.enemy[a->e->status].w * (iw->t.enemy[a->e->status].h
				* (i - tmp) / a->size));
			if (color != 0x880015)
				pixel_put_img(iw, x, i, color);
		}
	}
}

int		get_enemy_rot(t_mlx *iw, t_enemy *e)
{
	int x;
	int y;

	x = e->x - iw->p.x;
	y = e->y - iw->p.y;
	if (x > 0)
	{
		if (y < 0)
			return ((int)(atan(fabs((float)x / (float)y)) / 0.0174533));
		return (90 + (int)(atan(fabs((float)y / (float)x)) / 0.0174533));
	}
	else
	{
		if (y > 0)
			return (180 + (int)(atan(fabs((float)x / (float)y)) / 0.0174533));
		return (270 + (int)(atan(fabs((float)y / (float)x)) / 0.0174533));
	}
}

void	get_min_max_enemy_rot(t_mlx *iw, t_add_enemy *a, int ang)
{
	a->minrot = iw->p.rot - ang - 30;
	a->maxrot = iw->p.rot + ang + 30;
	if (a->minrot < 0)
	{
		a->minrot += 360;
		a->maxrot += 360;
		if (a->rot <= 90)
			a->rot += 360;
	}
	else if (a->maxrot > 360)
	{
		a->minrot -= 360;
		a->maxrot -= 360;
		if (a->rot >= 270)
			a->rot -= 360;
	}
}
