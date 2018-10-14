/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:19:09 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:19:15 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	draw_gun(t_mlx *iw)
{
	int i;
	int tmp;
	int tmp2;
	int tmp3;
	int j;

	i = WINDOW_X / 2 - iw->v.gun_size;
	tmp3 = i;
	tmp2 = WINDOW_Y - 2 * iw->v.gun_size;
	while (++i < WINDOW_X / 2 + iw->v.gun_size)
	{
		j = tmp2;
		while (++j < WINDOW_Y)
		{
			tmp = *((int *)(iw->t.gun[iw->v.gun_status].data) + (i - tmp3) *
				iw->t.gun[iw->v.gun_status].w / 2 / iw->v.gun_size +
				iw->t.gun[iw->v.gun_status].w * ((j - tmp2) *
					iw->t.gun[iw->v.gun_status].h / 2 / iw->v.gun_size));
			if (tmp != 0x880015)
				pixel_put_img(iw, i, j, tmp);
		}
	}
}

void	draw_bar(t_mlx *iw)
{
	mlx_put_image_to_window(iw->init, iw->win, iw->t.bar.ptr, 0, WINDOW_Y);
	if (iw->p.health > 50)
		mlx_put_image_to_window(iw->init, iw->win,
				iw->t.p[0].ptr, 460, WINDOW_Y);
	else if (iw->p.health > 20)
		mlx_put_image_to_window(iw->init, iw->win,
				iw->t.p[1].ptr, 460, WINDOW_Y);
	else
		mlx_put_image_to_window(iw->init, iw->win,
				iw->t.p[2].ptr, 460, WINDOW_Y);
	draw_numb(iw, iw->p.health, 680);
	draw_numb(iw, iw->p.lives, 340);
	draw_numb(iw, iw->p.score, 180);
	mlx_put_image_to_window(iw->init, iw->win,
			iw->t.key.ptr, 962, WINDOW_Y + 10);
	if (iw->f.miss == 1)
		mlx_put_image_to_window(iw->init, iw->win, iw->t.miss.ptr,
			WINDOW_X / 2 - 47, WINDOW_Y - 450 - (clock() -
			iw->f.shoot_time) * 100 / CLOCKS_PER_SEC);
}

void	draw_numb(t_mlx *iw, int numb, int x)
{
	char	*s;
	int		i;

	s = ft_itoa(numb);
	i = ft_strlen(s);
	while (--i >= 0)
		if (s[i] >= '0' && s[i] <= '9')
		{
			mlx_put_image_to_window(iw->init, iw->win,
					iw->t.numb[s[i] - '0'].ptr, x, WINDOW_Y + 65);
			x -= 40;
		}
	free(s);
}
