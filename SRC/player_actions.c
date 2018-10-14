/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:14:23 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:14:30 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	check_collisions(t_mlx *iw, t_draw2 *d)
{
	int		nx;
	int		ny;
	char	tmp;

	nx = iw->p.x + (d->nx * 5) * ((d->xdir == 1) ? 1 : -1);
	ny = iw->p.y + (d->ny * 5) * ((d->ydir == 1) ? 1 : -1);
	tmp = iw->m.map[ny / BSZ][nx / BSZ];
	if (tmp == '#' || tmp == 'd')
	{
		tmp = iw->m.map[ny / BSZ][iw->p.x / BSZ];
		if (tmp != '#' && tmp != 'd')
			iw->p.y = iw->p.y + d->ny * ((d->ydir == 1) ? 1 : -1);
		else
		{
			tmp = iw->m.map[iw->p.y / BSZ][nx / BSZ];
			if (tmp != '#' && tmp != 'd')
				iw->p.x = iw->p.x + d->nx * ((d->xdir == 1) ? 1 : -1);
		}
	}
	else
	{
		iw->p.x = iw->p.x + d->nx * ((d->xdir == 1) ? 1 : -1);
		iw->p.y = iw->p.y + d->ny * ((d->ydir == 1) ? 1 : -1);
	}
}

void	move(t_mlx *iw, int pl)
{
	t_draw2	d;
	float	k;

	d.ang = iw->p.rot + pl;
	get_dir(&d);
	k = get_k(d.ang);
	k *= 0.0174533;
	d.nx = fabs(cos(k)) * MOVING_SPEED;
	d.ny = fabs(sin(k)) * MOVING_SPEED;
	check_collisions(iw, &d);
}

void	check_action(t_mlx *iw)
{
	t_get_ray r;

	if (iw->f.door == 0)
	{
		get_ray(iw, WINDOW_X / 2, &r, 0);
		if (r.type == 'd' && r.dist <= BSZ)
		{
			r.tmp = iw->t.door.w - iw->t.door.w / 4;
			iw->v.door_plus = 0;
			iw->f.d = r;
			iw->f.door = 1;
			system("afplay -t 1 sounds/door.mp3 &");
		}
		else if (r.type == 'o' && r.dist <= BSZ)
		{
			iw->v.door_plus = iw->t.door.w - iw->t.door.w / 4 + 1;
			iw->m.map[r.ry][r.rx] = 'd';
			iw->f.d = r;
			iw->f.door = 2;
			system("afplay -t 1 sounds/door.mp3 &");
		}
	}
}
