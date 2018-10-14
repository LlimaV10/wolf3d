/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:06:14 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:06:22 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	check_sound(t_mlx *iw)
{
	if ((clock() - iw->s.environment) / CLOCKS_PER_SEC > 145)
	{
		system("afplay -t 62 sounds/environment.mp3 &");
		iw->s.environment = clock();
	}
	if (iw->f.forward == 1 || iw->f.back == 1 ||
			iw->f.right == 1 || iw->f.left == 1)
		if ((clock() - iw->s.step) / CLOCKS_PER_SEC >= 1)
		{
			system("afplay -v 0.5 sounds/step.mp3 &");
			iw->s.step = clock();
		}
}

void	actions(t_mlx *iw)
{
	if (iw->f.rotright == 1)
		iw->p.rot += (iw->p.rot < 360 - ROTATE_SPEED) ?
			ROTATE_SPEED : -360 + ROTATE_SPEED;
	if (iw->f.rotleft == 1)
		iw->p.rot += (iw->p.rot > ROTATE_SPEED) ?
			-ROTATE_SPEED : 360 - ROTATE_SPEED;
	if (iw->f.forward == 1)
		move(iw, 0);
	if (iw->f.back == 1)
		move(iw, (iw->p.rot < 180) ? 180 : -180);
	if (iw->f.right == 1)
		move(iw, 90);
	if (iw->f.left == 1)
		move(iw, -90);
}

void	shoot(t_mlx *iw)
{
	if (iw->v.gun_status == 0 && ((float)(clock() - iw->f.shoot_time) /
		(float)CLOCKS_PER_SEC > 0.3))
	{
		system("afplay -v 2 -t 1 sounds/shot.mp3 &");
		iw->v.gun_status = 1;
		damage_enemy(iw);
		iw->f.shoot_time = clock();
	}
	else if (iw->v.gun_status == 1 && ((float)(clock() - iw->f.shoot_time) /
		(float)CLOCKS_PER_SEC > 0.3))
	{
		iw->v.gun_status = 2;
		iw->f.miss = 0;
		iw->f.shoot_time = clock();
	}
	else if (iw->v.gun_status == 2 && ((float)(clock() - iw->f.shoot_time) /
		(float)CLOCKS_PER_SEC > 0.3))
	{
		iw->v.gun_status = 0;
		iw->f.shoot_time = clock();
		iw->f.shoot = 0;
	}
}

void	door1(t_mlx *iw)
{
	if (iw->v.door_plus < iw->f.d.tmp)
		iw->v.door_plus++;
	else
	{
		iw->v.door_plus = 0;
		iw->m.map[iw->f.d.ry][iw->f.d.rx] = 'o';
		iw->f.door = 0;
	}
}

void	door2(t_mlx *iw)
{
	if (iw->v.door_plus > 0)
		iw->v.door_plus--;
	else
		iw->f.door = 0;
}
