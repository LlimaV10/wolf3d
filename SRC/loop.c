/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:03:38 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:03:47 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		loop(t_mlx *iw)
{
	if (iw->p.health <= 0 && iw->f.dead == 0)
		iw->f.dead = 2;
	if (iw->p.health <= 0 && iw->f.dead != 1)
		dead(iw);
	if (iw->f.pause == 1)
		pause_f(iw);
	else if (iw->f.pause == -1)
		unpause_f(iw);
	check_sound(iw);
	if (iw->f.pause == 0 && iw->f.dead == 0)
	{
		actions(iw);
		if (iw->f.shoot == 1)
			shoot(iw);
		if (iw->f.door == 1)
			door1(iw);
		if (iw->f.door == 2)
			door2(iw);
		check_enemies(iw);
		update(iw);
	}
	return (0);
}

void	update(t_mlx *iw)
{
	mlx_destroy_image(iw->init, iw->img_ptr);
	iw->img_ptr = mlx_new_image(iw->init, WINDOW_X, WINDOW_Y);
	iw->img_data = mlx_get_data_addr(iw->img_ptr, &(iw->v.bpp),
			&(iw->v.size_line), &(iw->v.endian));
	mlx_clear_window(iw->init, iw->win);
	threads_draw(iw);
	draw_gun(iw);
	mlx_put_image_to_window(iw->init, iw->win, iw->img_ptr, 0, 0);
	draw_bar(iw);
}

void	dead(t_mlx *iw)
{
	if (iw->f.dead == 2)
	{
		mlx_clear_window(iw->init, iw->win);
		mlx_put_image_to_window(iw->init, iw->win, iw->t.dead[0].ptr, 0, 0);
		iw->f.dead_time = clock();
		iw->f.dead = 3;
	}
	else if (iw->f.dead == 3 && ((float)(clock() -
			iw->f.dead_time) / (float)CLOCKS_PER_SEC > 0.2))
	{
		mlx_clear_window(iw->init, iw->win);
		mlx_put_image_to_window(iw->init, iw->win, iw->t.dead[1].ptr, 0, 0);
		iw->f.dead_time = clock();
		iw->f.dead = 4;
	}
	else if (iw->f.dead == 4 && ((float)(clock() -
			iw->f.dead_time) / (float)CLOCKS_PER_SEC > 0.2))
	{
		mlx_clear_window(iw->init, iw->win);
		mlx_put_image_to_window(iw->init, iw->win, iw->t.dead[2].ptr, 0, 0);
		iw->f.dead_time = clock();
		iw->f.dead = 1;
	}
}

void	pause_f(t_mlx *iw)
{
	iw->f.pause = 2;
	update(iw);
	mlx_put_image_to_window(iw->init, iw->win,
			iw->t.pause.ptr, WINDOW_X / 2 - 250, 60);
}

void	unpause_f(t_mlx *iw)
{
	iw->f.pause = -2;
	update(iw);
	iw->f.pause = 0;
}
