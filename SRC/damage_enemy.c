/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:19:51 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:19:58 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		get_enemy2(t_mlx *iw, float k, t_enemy **tmp, t_get_enemy *g)
{
	if ((*tmp)->flag == 6)
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	g->len = (int)sqrtf(pow((*tmp)->x - iw->p.x, 2) +
			pow((*tmp)->y - iw->p.y, 2)) + 1;
	g->sz = WINDOW_Y * 120 / g->len;
	g->delta = atan((float)((*tmp)->y - iw->p.y) /
			(float)((*tmp)->x - iw->p.x + 0.000001));
	g->delta = (float)g->len * (float)g->sz / 200.0 * sin(k - g->delta);
	return (0);
}

void	get_enemy(t_mlx *iw, t_add_enemy *a, float k)
{
	t_enemy		*tmp;
	t_get_enemy	g;

	tmp = iw->e;
	a->size = 0;
	while (tmp != 0)
	{
		if (get_enemy2(iw, k, &tmp, &g) == 1)
			continue ;
		if ((int)fabs(g.delta) < g.sz / 4 && g.sz > a->size)
		{
			a->rot = get_enemy_rot(iw, tmp);
			get_min_max_enemy_rot(iw, a, iw->p.angle);
			if (a->rot > a->minrot && a->rot < a->maxrot)
			{
				a->e = tmp;
				a->delta = g.delta;
				a->size = g.sz;
				a->len = g.len;
			}
		}
		tmp = tmp->next;
	}
}

void	damage_enemy(t_mlx *iw)
{
	t_get_ray	r;
	t_add_enemy	a;

	a.e = 0;
	get_ray(iw, WINDOW_X / 2, &r, 0);
	get_enemy(iw, &a, r.k);
	if (a.e != 0)
	{
		if (a.len < BSZ * 7 && a.len < r.dist)
			a.e->health -= iw->p.damage;
		else
			iw->f.miss = 1;
	}
}
