/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements_to_draw.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:57:48 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 14:57:56 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../wolf.h"

t_element	*add_element2(t_draw2 *d)
{
	t_element *cr;

	cr = (t_element *)malloc(sizeof(t_element));
	cr->type = d->b;
	if (d->last_changed == 1)
	{
		cr->rx = d->add_el.rx + ((d->xdir == 1) ? BSZ / 2 : -BSZ / 2);
		cr->ry = (int)roundf(d->add_el.k * (float)cr->rx + d->add_el.b);
	}
	else
	{
		cr->ry = d->add_el.ry + ((d->ydir == 1) ? BSZ / 2 : -BSZ / 2);
		cr->rx = (int)roundf(((float)cr->ry - d->add_el.b) /
			(d->add_el.k + 0.000001));
	}
	return (cr);
}

void		add_element(t_element **start, t_draw2 *d, t_mlx *iw)
{
	t_element	*cr;
	char		tmp;

	cr = add_element2(d);
	tmp = 0;
	if (cr->ry / BSZ > 0 && cr->ry / BSZ < iw->m.y &&
		cr->rx / BSZ > 0 && cr->rx / BSZ < iw->m.x)
		tmp = iw->m.map[cr->ry / BSZ][cr->rx / BSZ];
	if (d->b == tmp)
	{
		cr->last_changed = d->last_changed;
		cr->next = *start;
		*start = cr;
	}
	else
		free(cr);
}

void		free_elements(t_element *els)
{
	t_element *tmp;

	while (els != 0)
	{
		tmp = els;
		els = els->next;
		free(tmp);
	}
}

void		delete_el(t_element **start, t_element *el)
{
	t_element *tmp;

	if (*start == el)
		*start = (*start)->next;
	else
	{
		tmp = *start;
		while (tmp->next != el)
			tmp = tmp->next;
		tmp->next = tmp->next->next;
	}
}

int			draw_el_get_pl(t_mlx *iw, t_element *el, t_tex *tex)
{
	int pl;

	pl = 0;
	if (el->type == 'd' || el->type == 'o')
		*tex = iw->t.door;
	if (el->type == 'o')
		pl = tex->w - tex->w / 4;
	if (el->type == 'd')
		pl = iw->v.door_plus;
	return (pl);
}
