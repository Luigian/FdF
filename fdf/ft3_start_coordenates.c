/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_coordenates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:00 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 03:58:58 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node	*move_pointer_to_top_right_corner(t_node *trav)
{
	while (trav->up)
		trav = trav->up;
	while (trav->right)
		trav = trav->right;
	return (trav);
}

void	assign_helper(t_node *adv, t_pro *p, t_map *map)
{
	adv->isox = p->isox;
	adv->isoy = p->isoy;
	adv->plax = p->plax;
	adv->play = p->play;
	adv->frox = p->frox;
	adv->froy = p->froy;
	p->isox += map->opp;
	p->isoy -= map->adj;
	p->plax += (map->opp * 1.2);
	p->frox += (map->opp * 1.2);
}

void	initialize_projection_helper(t_pro *p, t_map *map)
{
	p->isox = map->xs;
	p->isoy = map->ys;
	p->plax = map->xs;
	p->play = map->ys;
	p->frox = map->xs;
	p->froy = map->ys;
}

void	assign_coordenates(t_node *trav, t_map *map)
{
	t_node	*start;
	t_node	*adv;
	t_pro	*p;

	p = (t_pro *)malloc(sizeof(t_pro) * 1);
	initialize_projection_helper(p, map);
	start = trav;
	adv = trav;
	while (trav)
	{
		while (adv)
		{
			assign_helper(adv, p, map);
			adv = adv->right;
		}
		p->isox = trav->isox - map->opp;
		p->isoy = trav->isoy - map->adj;
		p->plax = trav->plax;
		p->play = trav->play - (map->opp * 1.2);
		p->frox = trav->frox;
		trav = trav->up;
		adv = trav;
	}
	free(p);
}

void	get_x_y_start(t_map *map)
{
	map->xs = (map->win_wide / 2) - ((map->cols - map->rows) * (map->opp / 2));
	map->ys = map->win_heigh - (map->win_wide / 16);
}
