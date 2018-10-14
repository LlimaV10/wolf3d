/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:22:52 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:23:00 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	get_def2(t_mlx *iw)
{
	iw->e = 0;
	iw->f.shoot = 0;
	iw->f.door = 0;
	iw->f.shoot_time = 0;
	iw->f.rotright = 0;
	iw->f.rotleft = 0;
	iw->f.forward = 0;
	iw->f.left = 0;
	iw->f.right = 0;
	iw->f.back = 0;
	iw->f.miss = 0;
	iw->f.pause = 1;
	iw->f.dead = 0;
	iw->start_mousex = -1;
	iw->s.environment = -200 * CLOCKS_PER_SEC;
	iw->s.step = -200 * CLOCKS_PER_SEC;
	iw->s.door = -200 * CLOCKS_PER_SEC;
	iw->s.shot = -200 * CLOCKS_PER_SEC;
	iw->s.enemyshot = -200 * CLOCKS_PER_SEC;
}

void	get_def(t_mlx *iw)
{
	iw->v.text_fill = 1;
	iw->avail = (char *)malloc(7);
	iw->avail[6] = '\0';
	iw->avail[0] = 's';
	iw->avail[1] = '.';
	iw->avail[2] = '#';
	iw->avail[3] = 'd';
	iw->avail[4] = 'o';
	iw->avail[5] = 'e';
	iw->m.y = 0;
	iw->m.x = 0;
	iw->p.rot = START_PLAYER_ROT;
	iw->p.angle = 23 * WINDOW_X / 700;
	iw->v.door_plus = 0;
	iw->p.health = 100;
	iw->p.score = 0;
	iw->p.lives = 0;
	iw->p.damage = 4;
	iw->v.gun_size = WINDOW_X / 7;
	iw->v.gun_status = 0;
	get_def2(iw);
}

int		check_textures(t_mlx *iw)
{
	int i;

	if (iw->t.t1.ptr == 0 || iw->t.t2.ptr == 0 || iw->t.t3.ptr == 0 ||
		iw->t.t4.ptr == 0 || iw->t.floor.ptr == 0 || iw->t.ceil.ptr == 0
		|| iw->t.door.ptr == 0 || iw->t.bar.ptr == 0 || iw->t.key.ptr == 0
		|| iw->t.miss.ptr == 0 || iw->t.pause.ptr == 0)
		return (1);
	i = -1;
	while (++i < 10)
		if (iw->t.enemy[i].ptr == 0)
			return (1);
	i = -1;
	while (++i < 3)
		if (iw->t.gun[i].ptr == 0 || iw->t.p[i].ptr == 0
				|| iw->t.dead[i].ptr == 0)
			return (1);
	i = -1;
	while (++i < 10)
		if (iw->t.numb[i].ptr == 0)
			return (1);
	return (0);
}
