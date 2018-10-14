/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:24:26 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 16:11:07 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		main(int argc, char **argv)
{
	int		fd;
	t_mlx	iw;

	if ((fd = check4err(argc, argv)) < 0)
		return (0);
	get_def(&iw);
	if (read_map(fd, &iw) == 0)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	iw.init = mlx_init();
	iw.win = mlx_new_window(iw.init, WINDOW_X, WINDOW_Y + 157, "wolf3d");
	iw.img_ptr = mlx_new_image(iw.init, WINDOW_X, WINDOW_Y);
	iw.img_data = mlx_get_data_addr(iw.img_ptr, &(iw.v.bpp),
		&(iw.v.size_line), &(iw.v.endian));
	iw.p.x = iw.p.sx;
	iw.p.y = iw.p.sy;
	get_textures(&iw);
	return (main2(&iw));
}

int		main2(t_mlx *iw)
{
	if (check_textures(iw) == 1)
	{
		write(1, "Error\n", 6);
		free(iw->avail);
		return (0);
	}
	get_textures_data(iw);
	threads_draw(iw);
	draw_gun(iw);
	mlx_put_image_to_window(iw->init, iw->win, iw->img_ptr, 0, 0);
	mlx_hook(iw->win, 2, 9, key_hook, iw);
	mlx_hook(iw->win, 3, 0, key_unpressed, iw);
	mlx_hook(iw->win, 17, 1L << 17, exit_x, iw);
	mlx_hook(iw->win, 6, 0, mouse_move, iw);
	signal(SIGINT, exit_s);
	mlx_loop_hook(iw->init, loop, iw);
	mlx_loop(iw->init);
	return (0);
}

void	exit_s(int i)
{
	system("killall afplay");
	i += i;
	exit(0);
}

void	pixel_put_img(t_mlx *iw, int x, int y, int color)
{
	int		*tmp;

	if ((x + WINDOW_X * y > 0) && (x + WINDOW_X * y < WINDOW_X * WINDOW_Y))
	{
		tmp = (int *)iw->img_data;
		tmp += x + WINDOW_X * y;
		*tmp = color;
	}
}
