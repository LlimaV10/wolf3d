/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:23:51 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:23:57 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	get_textures_data(t_mlx *iw)
{
	int i;

	iw->t.t1.data = mlx_get_data_addr(iw->t.t1.ptr,
		&(iw->t.t1.bpp), &(iw->t.t1.szln), &(iw->t.t1.endian));
	iw->t.t2.data = mlx_get_data_addr(iw->t.t2.ptr,
		&(iw->t.t2.bpp), &(iw->t.t2.szln), &(iw->t.t2.endian));
	iw->t.t3.data = mlx_get_data_addr(iw->t.t3.ptr,
		&(iw->t.t3.bpp), &(iw->t.t3.szln), &(iw->t.t3.endian));
	iw->t.t4.data = mlx_get_data_addr(iw->t.t4.ptr,
		&(iw->t.t4.bpp), &(iw->t.t4.szln), &(iw->t.t4.endian));
	iw->t.floor.data = mlx_get_data_addr(iw->t.floor.ptr,
		&(iw->t.floor.bpp), &(iw->t.floor.szln), &(iw->t.floor.endian));
	iw->t.ceil.data = mlx_get_data_addr(iw->t.ceil.ptr,
		&(iw->t.ceil.bpp), &(iw->t.ceil.szln), &(iw->t.ceil.endian));
	iw->t.door.data = mlx_get_data_addr(iw->t.door.ptr,
		&(iw->t.door.bpp), &(iw->t.door.szln), &(iw->t.door.endian));
	i = -1;
	while (++i < 10)
		iw->t.enemy[i].data = mlx_get_data_addr(iw->t.enemy[i].ptr,
			&(iw->t.enemy[i].bpp), &(iw->t.enemy[i].szln),
			&(iw->t.enemy[i].endian));
	i = -1;
	while (++i < 3)
		iw->t.gun[i].data = mlx_get_data_addr(iw->t.gun[i].ptr,
			&(iw->t.gun[i].bpp), &(iw->t.gun[i].szln), &(iw->t.gun[i].endian));
}

void	get_textures4(t_mlx *iw)
{
	iw->t.numb[8].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/8.xpm", &(iw->t.numb[8].w), &(iw->t.numb[8].h));
	iw->t.numb[9].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/9.xpm", &(iw->t.numb[9].w), &(iw->t.numb[9].h));
	iw->t.dead[0].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/DEAD/DEAD1.xpm", &(iw->t.dead[0].w), &(iw->t.dead[0].h));
	iw->t.dead[1].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/DEAD/DEAD2.xpm", &(iw->t.dead[1].w), &(iw->t.dead[1].h));
	iw->t.dead[2].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/DEAD/DEAD3.xpm", &(iw->t.dead[2].w), &(iw->t.dead[2].h));
}

void	get_textures3(t_mlx *iw)
{
	iw->t.p[0].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/menu/p1.xpm", &(iw->t.p[0].w), &(iw->t.p[0].h));
	iw->t.p[1].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/menu/p2.xpm", &(iw->t.p[1].w), &(iw->t.p[1].h));
	iw->t.p[2].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/menu/p3.xpm", &(iw->t.p[2].w), &(iw->t.p[2].h));
	iw->t.numb[0].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/0.xpm", &(iw->t.numb[0].w), &(iw->t.numb[0].h));
	iw->t.numb[1].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/1.xpm", &(iw->t.numb[1].w), &(iw->t.numb[1].h));
	iw->t.numb[2].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/2.xpm", &(iw->t.numb[2].w), &(iw->t.numb[2].h));
	iw->t.numb[3].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/3.xpm", &(iw->t.numb[3].w), &(iw->t.numb[3].h));
	iw->t.numb[4].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/4.xpm", &(iw->t.numb[4].w), &(iw->t.numb[4].h));
	iw->t.numb[5].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/5.xpm", &(iw->t.numb[5].w), &(iw->t.numb[5].h));
	iw->t.numb[6].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/6.xpm", &(iw->t.numb[6].w), &(iw->t.numb[6].h));
	iw->t.numb[7].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/numb/7.xpm", &(iw->t.numb[7].w), &(iw->t.numb[7].h));
	get_textures4(iw);
}

void	get_textures2(t_mlx *iw)
{
	iw->t.enemy[5].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e6.xpm", &(iw->t.enemy[5].w), &(iw->t.enemy[5].h));
	iw->t.enemy[6].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e7.xpm", &(iw->t.enemy[6].w), &(iw->t.enemy[6].h));
	iw->t.enemy[7].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e8.xpm", &(iw->t.enemy[7].w), &(iw->t.enemy[7].h));
	iw->t.enemy[8].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e9.xpm", &(iw->t.enemy[8].w), &(iw->t.enemy[8].h));
	iw->t.enemy[9].ptr = mlx_xpm_file_to_image(iw->init,
		"textures/enemy1/e10.xpm", &(iw->t.enemy[9].w), &(iw->t.enemy[9].h));
	iw->t.gun[0].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/gun/gun1.xpm", &(iw->t.gun[0].w), &(iw->t.gun[0].h));
	iw->t.gun[1].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/gun/gun2.xpm", &(iw->t.gun[1].w), &(iw->t.gun[1].h));
	iw->t.gun[2].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/gun/gun3.xpm", &(iw->t.gun[2].w), &(iw->t.gun[2].h));
	iw->t.bar.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/menu/menu.xpm", &(iw->t.bar.w), &(iw->t.bar.h));
	iw->t.key.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/menu/key.xpm", &(iw->t.key.w), &(iw->t.key.h));
	iw->t.miss.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/miss.xpm", &(iw->t.miss.w), &(iw->t.miss.h));
	iw->t.pause.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/PAUSE.xpm", &(iw->t.pause.w), &(iw->t.pause.h));
	get_textures3(iw);
}

void	get_textures(t_mlx *iw)
{
	iw->t.t1.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex1.xpm", &(iw->t.t1.w), &(iw->t.t1.h));
	iw->t.t2.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex4.xpm", &(iw->t.t2.w), &(iw->t.t2.h));
	iw->t.t3.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex5.xpm", &(iw->t.t3.w), &(iw->t.t3.h));
	iw->t.t4.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex6.xpm", &(iw->t.t4.w), &(iw->t.t4.h));
	iw->t.floor.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex3.xpm", &(iw->t.floor.w), &(iw->t.floor.h));
	iw->t.ceil.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/tex2.xpm", &(iw->t.ceil.w), &(iw->t.ceil.h));
	iw->t.door.ptr = mlx_xpm_file_to_image(iw->init,
			"textures/door.xpm", &(iw->t.door.w), &(iw->t.door.h));
	iw->t.enemy[0].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e1.xpm", &(iw->t.enemy[0].w), &(iw->t.enemy[0].h));
	iw->t.enemy[1].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e2.xpm", &(iw->t.enemy[1].w), &(iw->t.enemy[1].h));
	iw->t.enemy[2].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e3.xpm", &(iw->t.enemy[2].w), &(iw->t.enemy[2].h));
	iw->t.enemy[3].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e4.xpm", &(iw->t.enemy[3].w), &(iw->t.enemy[3].h));
	iw->t.enemy[4].ptr = mlx_xpm_file_to_image(iw->init,
			"textures/enemy1/e5.xpm", &(iw->t.enemy[4].w), &(iw->t.enemy[4].h));
	get_textures2(iw);
}
