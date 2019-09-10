/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rows_and_cols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:11:50 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 03:59:45 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_adjacent_and_opposite(t_map *map)
{
	int			sides;

	sides = (map->rows - 1) + (map->cols - 1);
	map->adj = (map->win_heigh - (map->win_wide / 8)) / sides;
	map->opp = map->adj * (tan(60 * 3.1416 / 180));
	while (((map->opp = map->adj * (tan(60 * 3.1416 / 180))) * sides) >\
		(map->win_wide - (map->win_wide / 8)))
		--map->adj;
}

int		struct_cols_counter(t_node *trav)
{
	int		cols;

	cols = 0;
	while (trav)
	{
		++cols;
		trav = trav->right;
	}
	return (cols);
}

int		struct_rows_counter(t_node *trav)
{
	int		rows;

	rows = 0;
	while (trav)
	{
		++rows;
		trav = trav->up;
	}
	return (rows);
}

void	get_rows_and_cols(t_node *beg, t_map *map)
{
	map->rows = struct_rows_counter(beg);
	map->cols = struct_cols_counter(beg);
	if (map->rows * map->cols >= 100)
	{
		map->win_heigh = 1080;
		map->win_wide = 1920;
	}
	if (map->rows * map->cols >= 1000)
	{
		map->win_heigh = 1440;
		map->win_wide = 2560;
	}
}

void	connect_up(t_node *prev, t_node *trav)
{
	trav->up = prev;
	prev->down = trav;
	while (trav->right)
	{
		prev = prev->right;
		trav = trav->right;
		trav->up = prev;
		prev->down = trav;
	}
}
