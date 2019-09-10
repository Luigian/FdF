/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deal_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:59 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 09:38:16 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	deal_key_ii(int key, void **param, t_map *map)
{
	if (key == 126)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->y -= 1;
		draw_grid(param);
	}
	if (key == 125)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->y += 1;
		draw_grid(param);
	}
}

void	free_structure(void **param)
{
	t_node	*beg;
	t_node	*trav;
	t_node	*kill;

	beg = (t_node *)(param[2]);
	while (beg)
	{
		kill = beg;
		trav = kill;
		beg = beg->down;
		while (trav)
		{
			trav = trav->left;
			free(kill);
			kill = trav;
		}
	}
}

void	free_last(t_map *map, void **param)
{
	t_co	*co;

	co = (t_co *)(param[4]);
	free(co);
	free(map);
	free_structure(param);
	free(param);
}

void	deal_key_i(int key, void **param, t_map *map)
{
	if (key == 53)
	{
		mlx_destroy_window(param[0], param[1]);
		free_last(map, param);
		exit(0);
	}
	if (key == 123)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->x -= 1;
		draw_grid(param);
	}
	if (key == 124)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->x += 1;
		draw_grid(param);
	}
}

int		deal_key(int key, void **param)
{
	t_node	*beg;
	t_map	*map;

	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	if (key == 53 || key == 123 || key == 123 || key == 124)
		deal_key_i(key, param, map);
	if (key == 126 || key == 125)
		deal_key_ii(key, param, map);
	if (key == 15)
		deal_key_iii(key, param, map);
	if (key == 69 || key == 78)
		deal_key_iv(key, param, map, beg);
	if (key == 47)
		deal_key_v(key, param, map);
	if (key == 43 || key == 49)
		deal_key_vi(key, param, map);
	return (0);
}
