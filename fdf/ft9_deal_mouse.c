/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deal_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:46:08 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 04:59:28 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		deal_mouse(int button, int x, int y, void **param)
{
	t_node	*beg;
	t_map	*map;

	x = 0;
	y = 0;
	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	if (button == 4)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->z -= 1;
		draw_grid(param);
	}
	if (button == 5)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->z += 1;
		draw_grid(param);
	}
	return (0);
}

void	deal_key_vi(int key, void **param, t_map *map)
{
	if (key == 43)
	{
		map->on = 0;
		draw_grid(param);
		if (map->proj == 1)
			map->proj = 2;
		else if (map->proj == 2)
			map->proj = 3;
		else if (map->proj == 3)
			map->proj = 1;
		map->on = 1;
		draw_grid(param);
	}
	if (key == 49)
	{
		map->on = 0;
		draw_grid(param);
		map->color += 1000;
		map->on = 1;
		draw_grid(param);
	}
}

void	deal_key_v(int key, void **param, t_map *map)
{
	if (key == 47)
	{
		map->on = 0;
		draw_grid(param);
		if (map->proj == 1)
			map->proj = 3;
		else if (map->proj == 3)
			map->proj = 2;
		else if (map->proj == 2)
			map->proj = 1;
		map->on = 1;
		draw_grid(param);
	}
}

void	deal_key_iv(int key, void **param, t_map *map, t_node *beg)
{
	if (key == 69)
	{
		map->on = 0;
		draw_grid(param);
		map->zoom -= 1;
		map->on = 1;
		draw_grid(param);
	}
	if (key == 78)
	{
		map->on = 0;
		draw_grid(param);
		if (((beg->isoy + ((((map->ys - beg->isoy) * ZOOM_SPEED) / 100)\
			* map->zoom)) + 0) < map->ys)
			map->zoom += 1;
		map->on = 1;
		draw_grid(param);
	}
}

void	deal_key_iii(int key, void **param, t_map *map)
{
	if (key == 15)
	{
		map->on = 0;
		draw_grid(param);
		if (!map->color)
		{
			map->z = 0;
			map->x = 0;
			map->y = 0;
			map->zoom = 0;
		}
		else
			map->color = 0;
		map->on = 1;
		draw_grid(param);
	}
}
