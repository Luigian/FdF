/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:12:13 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 09:37:15 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_square(void **param)
{
	int		x;
	int		y;

	x = 20;
	while (x < 269)
	{
		y = 20;
		while (y < 180)
		{
			mlx_pixel_put(param[0], param[1], x, y, 8881798);
			++y;
		}
		++x;
	}
}

void	draw_cols(void **param, t_node *trav, t_map *map, t_co *co)
{
	t_node	*adv;

	adv = trav;
	while (trav)
	{
		while (adv->down)
		{
			map->proj == 1 ? x_y_iso(adv, adv->down, param, co) : 0;
			map->proj == 2 ? x_y_plan(adv, adv->down, param, co) : 0;
			map->proj == 3 ? x_y_front(adv, adv->down, param, co) : 0;
			draw_line(param, co, adv, adv->down);
			adv = adv->down;
		}
		trav = trav->left;
		adv = trav;
	}
}

void	draw_rows(void **param, t_node *trav, t_map *map, t_co *co)
{
	t_node	*adv;

	adv = trav;
	while (trav)
	{
		while (adv->left)
		{
			map->proj == 1 ? x_y_iso(adv, adv->left, param, co) : 0;
			map->proj == 2 ? x_y_plan(adv, adv->left, param, co) : 0;
			map->proj == 3 ? x_y_front(adv, adv->left, param, co) : 0;
			draw_line(param, co, adv, adv->left);
			adv = adv->left;
		}
		trav = trav->down;
		adv = trav;
	}
}

void	draw_grid(void **param)
{
	t_node	*trav;
	t_map	*map;
	t_co	*co;

	trav = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	co = (t_co *)(param[4]);
	draw_rows(param, trav, map, co);
	draw_cols(param, trav, map, co);
	draw_square(param);
	draw_text_menu(param);
}

void	open_graphic_interface(t_node *beg, t_map *map)
{
	void		**param;
	void		*mlx_ptr;
	void		*win_ptr;
	t_co		*co;

	co = (t_co *)malloc(sizeof(t_co) * 1);
	param = (void **)malloc(sizeof(void *) * 5);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, map->win_wide, map->win_heigh, "fdf");
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	param[2] = beg;
	param[3] = map;
	param[4] = co;
	draw_grid(param);
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_mouse_hook(win_ptr, deal_mouse, param);
	mlx_loop(mlx_ptr);
}
