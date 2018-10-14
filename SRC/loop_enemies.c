/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:09:37 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:09:44 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	check_enemies(t_mlx *iw)
{
	t_check_enemy	chk;
	t_enemy			*tmp;

	tmp = iw->e;
	while (tmp != 0)
	{
		if (tmp->flag != 6)
		{
			if (tmp->health <= 0 && tmp->flag < 4)
				tmp->flag = 4;
			chk.len = (int)sqrtf(pow(iw->p.x - tmp->x, 2) +
					pow(iw->p.y - tmp->y, 2));
			check_enemies2(iw, tmp, &chk);
		}
		tmp = tmp->next;
	}
}

void	check_enemies2(t_mlx *iw, t_enemy *tmp, t_check_enemy *chk)
{
	if (chk->len < BSZ * 7)
	{
		chk->a.rot = get_enemy_rot(iw, tmp);
		get_ray(iw, -1, &(chk->r), (float)chk->a.rot);
		chk->rlen = (int)sqrtf(pow(iw->p.x - chk->r.rx, 2) +
				pow(iw->p.y - chk->r.ry, 2));
		check_enemy_action(tmp, chk, iw);
	}
	else if (tmp->flag < 4)
	{
		tmp->flag = 0;
		tmp->status = 1;
	}
}

void	check_enemy_action(t_enemy *tmp, t_check_enemy *chk, t_mlx *iw)
{
	if (tmp->flag == 0)
	{
		if (chk->len < chk->rlen)
		{
			if (chk->len > BSZ * 3)
			{
				tmp->flag = 1;
				move_enemy(iw, tmp, chk);
				if ((float)(clock() - tmp->time) / (float)CLOCKS_PER_SEC < 0.3)
					return ;
				tmp->status += ((tmp->status >= 3) ? -tmp->status : 1);
				tmp->time = clock();
			}
			else
				tmp->flag = 2;
		}
	}
	else
		check_enemy_action2(tmp, chk, iw);
}

void	check_enemy_action2(t_enemy *tmp, t_check_enemy *chk, t_mlx *iw)
{
	if (tmp->flag == 1)
	{
		if (chk->len > BSZ * 3 || chk->len > chk->rlen)
		{
			move_enemy(iw, tmp, chk);
			if ((float)(clock() - tmp->time) / (float)CLOCKS_PER_SEC < 0.3)
				return ;
			tmp->status += ((tmp->status >= 3) ? -tmp->status : 1);
			tmp->time = clock();
		}
		else
			tmp->flag = 2;
	}
	else if (tmp->flag == 5)
	{
		if ((float)(clock() - tmp->time) / (float)CLOCKS_PER_SEC < 0.5)
			return ;
		tmp->status += 1;
		tmp->time = clock();
		if (tmp->status == 9)
			tmp->flag = 6;
	}
	else
		check_enemy_action3(tmp, chk, iw);
}

void	check_enemy_action3(t_enemy *tmp, t_check_enemy *chk, t_mlx *iw)
{
	if (tmp->flag == 2)
	{
		if (chk->len <= BSZ * 3 && chk->len < chk->rlen)
		{
			tmp->status = 4;
			tmp->time = clock();
			tmp->flag = 3;
		}
		else
			tmp->flag = 1;
	}
	else if (tmp->flag == 4)
	{
		tmp->flag = 5;
		tmp->status = 7;
		tmp->time = clock();
		iw->p.score += 1;
	}
	else
		check_enemy_action4(tmp, chk, iw);
}
