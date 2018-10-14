/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:21:02 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 16:07:02 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		key_hook2(int keycode, t_mlx *iw)
{
	if (keycode == 116 || keycode == 17)
		iw->v.text_fill += (iw->v.text_fill > 0) ? -1 : 1;
	else if (keycode == 102 || keycode == 3)
		check_action(iw);
	else if (keycode == 32 || keycode == 49)
		iw->f.shoot = 1;
	else if (keycode == 112 || keycode == 35)
		iw->f.pause = ((iw->f.pause == 0) ? 1 : -1);
	return (0);
}

int		key_hook(int keycode, t_mlx *iw)
{
	if (keycode == 53 || keycode == 65307 || iw->f.dead == 1)
	{
		free(iw->avail);
		free_map(iw);
		system("killall afplay");
		exit(0);
	}
	else if (keycode == 65363 || keycode == 124)
		iw->f.rotright = 1;
	else if (keycode == 65361 || keycode == 123)
		iw->f.rotleft = 1;
	else if (keycode == 119 || keycode == 13 || keycode == 126)
		iw->f.forward = 1;
	else if (keycode == 115 || keycode == 1 || keycode == 125)
		iw->f.back = 1;
	else if (keycode == 97 || keycode == 0)
		iw->f.left = 1;
	else if (keycode == 100 || keycode == 2)
		iw->f.right = 1;
	else
		return (key_hook2(keycode, iw));
	return (0);
}

int		key_unpressed(int keycode, t_mlx *iw)
{
	if (keycode == 65363 || keycode == 124)
		iw->f.rotright = 0;
	else if (keycode == 65361 || keycode == 123)
		iw->f.rotleft = 0;
	else if (keycode == 119 || keycode == 13 || keycode == 126)
		iw->f.forward = 0;
	else if (keycode == 115 || keycode == 1 || keycode == 125)
		iw->f.back = 0;
	else if (keycode == 97 || keycode == 0)
		iw->f.left = 0;
	else if (keycode == 100 || keycode == 2)
		iw->f.right = 0;
	return (0);
}

int		mouse_move(int x, int y, t_mlx *iw)
{
	y += y;
	if (iw->start_mousex == -1)
		iw->start_mousex = x;
	if (iw->start_mousex > x)
		iw->p.rot -= 2;
	else if (iw->start_mousex < x)
		iw->p.rot += 2;
	else if (x == -100)
		iw->p.rot -= 2;
	else if (x == 2459)
		iw->p.rot += 2;
	iw->start_mousex = x;
	while (iw->p.rot > 360)
		iw->p.rot -= 360;
	while (iw->p.rot < 0)
		iw->p.rot += 360;
	return (0);
}

int		exit_x(t_mlx *iw)
{
	free(iw->avail);
	system("killall afplay");
	exit(0);
	return (0);
}
