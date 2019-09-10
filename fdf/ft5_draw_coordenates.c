/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft5_draw_coordenates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:27 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 04:13:05 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	increase_window(t_map *map, void **param, t_node *beg)
{
	t_co	*co;

	co = (t_co *)(param[4]);
	map->win_heigh = 1440;
	map->win_wide = 2560;
	map->x = 0;
	map->y = 0;
	mlx_destroy_window(param[0], param[1]);
	free(co);
	free(param);
	open_graphic_interface(beg, map);
}

void	x_y_front(t_node *a, t_node *b, void **param, t_co *co)
{
	t_map	*map;
	t_node	*beg;

	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	co->x0 = a->frox + ((((map->xs - a->frox) * ZOOM_SPEED) / 100) * map->zoom);
	co->y0 = a->froy + ((((map->ys - a->froy) * ZOOM_SPEED) / 100) * map->zoom);
	co->x1 = b->frox + ((((map->xs - b->frox) * ZOOM_SPEED) / 100) * map->zoom);
	co->y1 = b->froy + ((((map->ys - b->froy) * ZOOM_SPEED) / 100) * map->zoom);
	co->x0 += (map->x * X_Y_SPEED);
	co->y0 += (a->z * (map->z * Z_SPEED)) + (map->y * X_Y_SPEED);
	co->x1 += (map->x * X_Y_SPEED);
	co->y1 += (b->z * (map->z * Z_SPEED)) + (map->y * X_Y_SPEED);
	co->x0c = co->x0;
	co->y0c = co->y0;
	co->x1c = co->x1;
	co->y1c = co->y1;
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 || \
		co->x1 > map->win_wide || co->y0 < 0 || co->y0 > map->win_heigh ||\
		co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	x_y_plan(t_node *a, t_node *b, void **param, t_co *co)
{
	t_map	*map;
	t_node	*beg;

	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	co->x0 = a->plax + ((((map->xs - a->plax) * ZOOM_SPEED) / 100) * map->zoom);
	co->y0 = a->play + ((((map->ys - a->play) * ZOOM_SPEED) / 100) * map->zoom);
	co->x1 = b->plax + ((((map->xs - b->plax) * ZOOM_SPEED) / 100) * map->zoom);
	co->y1 = b->play + ((((map->ys - b->play) * ZOOM_SPEED) / 100) * map->zoom);
	co->x0 += (map->x * X_Y_SPEED);
	co->y0 += (map->y * X_Y_SPEED);
	co->x1 += (map->x * X_Y_SPEED);
	co->y1 += (map->y * X_Y_SPEED);
	co->x0c = co->x0;
	co->y0c = co->y0;
	co->x1c = co->x1;
	co->y1c = co->y1;
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 ||\
		co->x1 > map->win_wide || co->y0 < 0 || co->y0 > map->win_heigh ||\
		co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	x_y_iso(t_node *a, t_node *b, void **param, t_co *co)
{
	t_map	*map;
	t_node	*beg;

	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	co->x0 = a->isox + ((((map->xs - a->isox) * ZOOM_SPEED) / 100) * map->zoom);
	co->y0 = a->isoy + ((((map->ys - a->isoy) * ZOOM_SPEED) / 100) * map->zoom);
	co->x1 = b->isox + ((((map->xs - b->isox) * ZOOM_SPEED) / 100) * map->zoom);
	co->y1 = b->isoy + ((((map->ys - b->isoy) * ZOOM_SPEED) / 100) * map->zoom);
	co->x0 += (map->x * X_Y_SPEED);
	co->y0 += (a->z * (map->z * Z_SPEED)) + (map->y * X_Y_SPEED);
	co->x1 += (map->x * X_Y_SPEED);
	co->y1 += (b->z * (map->z * Z_SPEED)) + (map->y * X_Y_SPEED);
	co->x0c = co->x0;
	co->y0c = co->y0;
	co->x1c = co->x1;
	co->y1c = co->y1;
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 ||\
		co->x1 > map->win_wide || co->y0 < 0 || co->y0 > map->win_heigh ||\
		co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	draw_text_menu(void **param)
{
	mlx_string_put(param[0], param[1], 50, 30, 0xFFFFFF, "View : < and >");
	mlx_string_put(param[0], param[1], 50, 50, 0xFFFFFF, "Rise : mouse scroll");
	mlx_string_put(param[0], param[1], 50, 70, 0xFFFFFF, "Place : arrow keys");
	mlx_string_put(param[0], param[1], 50, 90, 0xFFFFFF, "Zoom : + and -");
	mlx_string_put(param[0], param[1], 50, 110, 0xFFFFFF, "Color : space bar");
	mlx_string_put(param[0], param[1], 50, 130, 0xFFFFFF, "Reset : R");
	mlx_string_put(param[0], param[1], 50, 150, 0xFFFFFF, "Exit : esc");
}
