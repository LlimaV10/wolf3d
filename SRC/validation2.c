/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:46:41 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:46:51 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

void	add_enemy(t_mlx *iw, int x, int y)
{
	t_enemy	*cr;

	cr = (t_enemy *)malloc(sizeof(t_enemy));
	cr->x = x * BSZ + 150;
	cr->y = y * BSZ + 150;
	cr->damage = 2;
	cr->health = 10;
	cr->status = 1;
	cr->flag = 0;
	cr->time = 0;
	cr->next = iw->e;
	iw->e = cr;
}

int		check_string_map_i(char *s, t_mlx *iw, char *start, int i)
{
	if (s[i] == iw->avail[0])
	{
		iw->p.sx = i * BSZ + 150;
		iw->p.sy = iw->m.y * BSZ + 150;
		*start = 1;
		return (1);
	}
	else if (s[i] == 'e')
	{
		add_enemy(iw, i, iw->m.y);
		s[i] = '.';
	}
	return (0);
}

int		check_string_map(char *s, t_mlx *iw, char *start)
{
	int				len;
	int				i;
	unsigned int	j;
	char			b;

	if ((len = ft_strlen(s)) == 0)
		return (0);
	i = -1;
	while (++i < len)
	{
		if (check_string_map_i(s, iw, start, i) == 1)
			continue ;
		b = 0;
		j = 0;
		while (++j < ft_strlen(iw->avail))
			if (s[i] == iw->avail[j])
			{
				b = 1;
				break ;
			}
		if (b == 0)
			return (0);
	}
	return (1);
}

void	add_map_line(char *s, t_map_list **m, t_mlx *iw)
{
	t_map_list *tmp;
	t_map_list *tmp2;

	iw->m.y++;
	tmp = (t_map_list *)malloc(sizeof(t_map_list));
	tmp->next = 0;
	tmp->s = s;
	if (*m == 0)
		*m = tmp;
	else
	{
		tmp2 = *m;
		while (tmp2->next != 0)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
}

void	clear_map_lst(t_map_list *m)
{
	t_map_list *tmp;

	while (m != 0)
	{
		tmp = m;
		m = m->next;
		free(tmp->s);
		free(tmp);
	}
}
