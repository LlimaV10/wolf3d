/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_enemies_to_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:56:32 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:56:39 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

int		get_el_len(t_mlx *iw, t_element *el)
{
	if (el->type == 'e')
		return (el->a.len);
	else
		return ((int)sqrtf(pow(iw->p.x - el->rx, 2) +
			pow(iw->p.y - el->ry, 2)));
}

void	insert_el_after(t_element *dest, t_element *el)
{
	t_element *tmp;

	if (dest->next == 0)
	{
		dest->next = el;
		el->next = 0;
	}
	else
	{
		tmp = dest->next;
		dest->next = el;
		el->next = tmp;
	}
}

void	add_enemies_to_elements2(t_draw2 *d, t_element *start, t_mlx *iw)
{
	t_element *tmp;
	t_element *el;

	while (start != 0)
	{
		tmp = start->next;
		if (d->els == 0 || get_el_len(iw, d->els) < start->a.len)
		{
			start->next = d->els;
			d->els = start;
		}
		else
		{
			el = d->els;
			while (el->next != 0 && get_el_len(iw, el->next) >= start->a.len)
				el = el->next;
			insert_el_after(el, start);
		}
		start = tmp;
	}
}

void	add_enemies2(t_element **start, t_enemy **tmp, t_element *cr)
{
	if ((int)fabs(cr->a.delta) < cr->a.size / 4)
	{
		cr->a.e = *tmp;
		cr->next = *start;
		*start = cr;
	}
	else
		free(cr);
}

void	add_enemies(t_draw2 *d, t_mlx *iw)
{
	t_enemy		*tmp;
	t_element	*cr;
	t_element	*start;

	start = 0;
	tmp = iw->e;
	while (tmp != 0)
	{
		cr = (t_element *)malloc(sizeof(t_element));
		cr->type = 'e';
		cr->a.len = (int)sqrtf(pow(tmp->x - iw->p.x, 2) +
				pow(tmp->y - iw->p.y, 2)) + 1;
		cr->a.size = WINDOW_Y * 120 / cr->a.len;
		cr->a.delta = atan((float)(tmp->y - iw->p.y) /
				(float)(tmp->x - iw->p.x + 0.0001));
		cr->a.delta = (float)cr->a.len * (float)cr->a.size / 200.0 *
			sin(d->add_el.k - cr->a.delta) * ((d->xdir == 1) ? 1 : -1);
		add_enemies2(&start, &tmp, cr);
		tmp = tmp->next;
	}
	add_enemies_to_elements2(d, start, iw);
}
