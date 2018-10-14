/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:45:08 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:45:23 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		get_max_map_len(t_mlx *iw, t_map_list *m)
{
	int curr_max;
	int l;
	int i;

	curr_max = ft_strlen(m->s);
	m = m->next;
	i = 0;
	while (++i < iw->m.y)
	{
		if ((l = ft_strlen(m->s)) > curr_max)
			curr_max = l;
		m = m->next;
	}
	return (curr_max);
}

void	rewrite_map(t_mlx *iw, t_map_list *m)
{
	int	i;
	int tmp;

	iw->m.x = get_max_map_len(iw, m);
	iw->m.x += 2;
	iw->m.y += 2;
	iw->m.map = (char **)malloc(iw->m.y * sizeof(char *));
	iw->m.map[0] = (char *)malloc((iw->m.x + 1) * sizeof(char));
	ft_memset(iw->m.map[0], '#', iw->m.x);
	iw->m.map[0][iw->m.x] = '\0';
	iw->m.map[iw->m.y - 1] = (char *)malloc((iw->m.x + 1) * sizeof(char));
	ft_memset(iw->m.map[iw->m.y - 1], '#', iw->m.x);
	iw->m.map[iw->m.y - 1][iw->m.x] = '\0';
	i = 0;
	while (++i < iw->m.y - 1)
	{
		iw->m.map[i] = (char *)malloc((iw->m.x + 1) * sizeof(char));
		iw->m.map[i][0] = '#';
		iw->m.map[i][iw->m.x] = '\0';
		tmp = ft_strlen(m->s);
		ft_memcpy(iw->m.map[i] + 1, m->s, tmp);
		ft_memset(iw->m.map[i] + 1 + tmp, '#', iw->m.x - tmp - 1);
		m = m->next;
	}
}

void	free_map(t_mlx *iw)
{
	int i;

	i = -1;
	while (++i < iw->m.y)
		free(iw->m.map[i]);
	free(iw->m.map);
}

int		read_map(int fd, t_mlx *iw)
{
	char		*s;
	t_map_list	*m;
	char		start;

	start = 0;
	m = 0;
	while (get_next_line(fd, &s) > 0)
	{
		if (check_string_map(s, iw, &start) == 0)
		{
			free(s);
			clear_map_lst(m);
			return (0);
		}
		add_map_line(s, &m, iw);
	}
	if (start == 0 || s != 0)
	{
		free(s);
		clear_map_lst(m);
		return (0);
	}
	rewrite_map(iw, m);
	clear_map_lst(m);
	return (1);
}

int		check4err(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		write(1, "usage: wolf3d map_name\n", 23);
		return (-1);
	}
	if ((fd = open(argv[1], O_DIRECTORY)) > 0)
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	close(fd);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		write(1, "Error\n", 6);
	return (fd);
}
