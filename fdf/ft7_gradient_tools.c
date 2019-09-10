/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gradient_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:45 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 05:02:48 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_arrays_int(int *d, int *s, int *err)
{
	free(d);
	free(s);
	free(err);
}

void	get_coor_next_pixel(t_co *co, int *d, int *s, int *err)
{
	err[1] = err[0];
	if (err[1] > -(d[0]))
	{
		err[0] -= d[1];
		co->x0 += s[0];
	}
	if (err[1] < d[1])
	{
		err[0] += d[0];
		co->y0 += s[1];
	}
}

int		calculate_channel(int percent, int a_color, int b_color)
{
	int		result;

	result = 0;
	result = a_color - (((a_color - b_color) * percent) / 100);
	return (result);
}

void	get_node_b_new_colors(t_node *b, t_colo *colo, t_map *map)
{
	colo->r2 = 65 + map->color;
	colo->g2 = 50 + map->color;
	colo->b2 = 0 + map->color;
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 1)))
	{
		colo->r2 = 220 + map->color;
		colo->g2 = 170 + map->color;
		colo->b2 = 0 + map->color;
	}
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 2)))
	{
		colo->r2 = 255 + map->color;
		colo->g2 = 255 + map->color;
		colo->b2 = 0 + map->color;
	}
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 3)))
	{
		colo->r2 = 255 + map->color;
		colo->g2 = 255 + map->color;
		colo->b2 = 200 + map->color;
	}
}

void	get_node_a_new_colors(t_node *a, t_colo *colo, t_map *map)
{
	colo->r1 = 65 + map->color;
	colo->g1 = 50 + map->color;
	colo->b1 = 0 + map->color;
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 1)))
	{
		colo->r1 = 220 + map->color;
		colo->g1 = 170 + map->color;
		colo->b1 = 0 + map->color;
	}
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 2)))
	{
		colo->r1 = 255 + map->color;
		colo->g1 = 255 + map->color;
		colo->b1 = 0 + map->color;
	}
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 3)))
	{
		colo->r1 = 255 + map->color;
		colo->g1 = 255 + map->color;
		colo->b1 = 200 + map->color;
	}
}
