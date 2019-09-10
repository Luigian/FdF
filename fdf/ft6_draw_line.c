/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:37 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 09:37:43 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		currcolor_bon(int perc, t_node *a, t_node *b, void **param)
{
	t_colo	*colo;
	t_map	*map;
	int		ret;

	colo = (t_colo *)malloc(sizeof(t_colo) * 1);
	map = (t_map *)(param[3]);
	get_node_a_new_colors(a, colo, map);
	get_node_b_new_colors(b, colo, map);
	if (colo->r1 == colo->r2 && colo->g1 == colo->g2 && colo->b1 == colo->b2)
	{
		colo->curr_red = colo->r1;
		colo->curr_green = colo->g1;
		colo->curr_blue = colo->b1;
	}
	else
	{
		colo->curr_red = calculate_channel(perc, colo->r1, colo->r2);
		colo->curr_green = calculate_channel(perc, colo->g1, colo->g2);
		colo->curr_blue = calculate_channel(perc, colo->b1, colo->b2);
	}
	colo->curr_red = 16711680 - ((255 - colo->curr_red) * 65536);
	colo->curr_green = (colo->curr_green * 65280) / 255;
	ret = colo->curr_red + colo->curr_green + colo->curr_blue;
	free(colo);
	return (ret);
}

int		currcolor_nat(int perc, t_node *a, t_node *b)
{
	int		curr_red;
	int		curr_green;
	int		curr_blue;

	if (a->color.red == b->color.red && a->color.green == b->color.green\
		&& a->color.blue == b->color.blue)
	{
		curr_red = a->color.red;
		curr_green = a->color.green;
		curr_blue = a->color.blue;
	}
	else
	{
		curr_red = calculate_channel(perc, a->color.red, b->color.red);
		curr_green = calculate_channel(perc, a->color.green, b->color.green);
		curr_blue = calculate_channel(perc, a->color.blue, b->color.blue);
	}
	curr_red = 16711680 - ((255 - curr_red) * 65536);
	curr_green = (curr_green * 65280) / 255;
	return (curr_red + curr_green + curr_blue);
}

int		perc_calc(int curr, int start, int end)
{
	int		placement;
	int		distance;

	if ((distance = end - start) < 0)
		distance *= -1;
	if ((placement = curr - start) < 0)
		placement *= -1;
	!distance ? distance = 1 : 0;
	return ((placement * 100) / distance);
}

void	get_draw_metrics(t_co *co, int *d, int *s, int *err)
{
	d[0] = abs(co->x1 - co->x0);
	d[1] = abs(co->y1 - co->y0);
	s[0] = co->x0 < co->x1 ? 1 : -1;
	s[1] = co->y0 < co->y1 ? 1 : -1;
	err[0] = (d[0] > d[1] ? d[0] : -(d[1])) / 2;
}

void	draw_line(void **param, t_co *co, t_node *a, t_node *b)
{
	int		*d;
	int		*s;
	int		*err;
	int		color;
	int		percent;

	d = (int *)malloc(sizeof(int) * 2);
	s = (int *)malloc(sizeof(int) * 2);
	err = (int *)malloc(sizeof(int) * 2);
	get_draw_metrics(co, d, s, err);
	while (1)
	{
		percent = d[0] >= d[1] ? perc_calc(co->x0, co->x0c, co->x1c) :\
			perc_calc(co->y0, co->y0c, co->y1c);
		if (((t_map *)(param[3]))->on)
			color = ((t_map *)(param[3]))->color ? currcolor_bon(percent,\
			a, b, param) : currcolor_nat(percent, a, b);
		else
			color = 0;
		mlx_pixel_put(param[0], param[1], co->x0, co->y0, color);
		if (co->x0 == co->x1 && co->y0 == co->y1)
			break ;
		get_coor_next_pixel(co, d, s, err);
	}
	free_arrays_int(d, s, err);
}
