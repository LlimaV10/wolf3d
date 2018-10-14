/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_enemies2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:10:52 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:10:59 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	check_enemy_action4(t_enemy *tmp, t_check_enemy *chk, t_mlx *iw)
{
	if (tmp->flag == 3)
	{
		if (chk->len <= BSZ * 3 && chk->len < chk->rlen)
		{
			if ((clock() - iw->s.enemyshot) * 5 / 2 / CLOCKS_PER_SEC >= 1)
			{
				system("afplay -v 0.5 sounds/enemyshot.mp3 &");
				iw->s.enemyshot = clock();
			}
			if ((float)(clock() - tmp->time) / (float)CLOCKS_PER_SEC < 0.3)
				return ;
			check_enemy_action5(tmp, iw);
		}
		else
			tmp->flag = 1;
	}
}

void	check_enemy_action5(t_enemy *tmp, t_mlx *iw)
{
	if (tmp->status == 4)
	{
		tmp->status = 5;
		tmp->time = clock();
	}
	else if (tmp->status == 5)
	{
		tmp->status = 6;
		tmp->time = clock();
		iw->p.health -= tmp->damage;
	}
	else
	{
		tmp->status = 5;
		tmp->time = clock();
	}
}

void	move_enemy(t_mlx *iw, t_enemy *e, t_check_enemy *chk)
{
	t_draw2	d;
	float	k;

	d.ang = chk->a.rot + ((chk->a.rot < 180) ? 180 : -180);
	get_dir(&d);
	k = get_k(d.ang);
	k *= 0.0174533;
	d.nx = fabs(cos(k)) * ENEMY_SPEED;
	d.ny = fabs(sin(k)) * ENEMY_SPEED;
	check_enemy_collisions(iw, &d, e);
}

void	check_enemy_collisions(t_mlx *iw, t_draw2 *d, t_enemy *e)
{
	int		nx;
	int		ny;
	char	tmp;

	nx = e->x + (d->nx * 5) * ((d->xdir == 1) ? 1 : -1);
	ny = e->y + (d->ny * 5) * ((d->ydir == 1) ? 1 : -1);
	tmp = iw->m.map[ny / BSZ][nx / BSZ];
	if (tmp == '#' || tmp == 'd')
	{
		tmp = iw->m.map[(e->y + ENEMY_SPEED *
				((d->ydir == 1) ? 1 : -1)) / BSZ][e->x / BSZ];
		if (tmp != '#' && tmp != 'd')
			e->y = e->y + ENEMY_SPEED * ((d->ydir == 1) ? 1 : -1);
		else
		{
			tmp = iw->m.map[e->y / BSZ][(e->x + ENEMY_SPEED *
					((d->xdir == 1) ? 1 : -1)) / BSZ];
			if (tmp != '#' && tmp != 'd')
				e->x = e->x + ENEMY_SPEED * ((d->xdir == 1) ? 1 : -1);
		}
		return ;
	}
	e->x = e->x + d->nx * ((d->xdir == 1) ? 1 : -1);
	e->y = e->y + d->ny * ((d->ydir == 1) ? 1 : -1);
}
