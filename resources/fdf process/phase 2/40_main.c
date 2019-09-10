/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 02:06:03 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	open_graphic_interface(t_node *beg, t_map *map);

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	print_error_and_exit(int code)
{
	if (code == 1)
	{
		write(1, "Usage : ./fdf <filename>\n", 25);
		exit (code);
	}
	else if (code == 2)
	{
		write(1, "Invalid file. Exiting\n", 22);
		exit (code);
	}
	else if (code == 3)
	{
		write(1, "Found wrong line length. Exiting.\n", 34);
		exit (code);
	}
}

void	draw_grid(void **param);

void	increase_decrease_y_coordenate(void **param, int dir)
{
	t_node		*trav;
	t_node		*beg;

	trav =  (t_node *)(param[2]);
	while (trav)
	{
		beg = trav;
		while (trav)
		{
			trav->isoy = trav->isoy - (trav->z * (dir ? Z_SPEED : (-Z_SPEED))); 
			trav = trav->left;
		}
		trav = beg->down;
	}
}

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
	
void	deal_key_helper_six(int key, void **param, t_map *map)
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

void	deal_key_helper_five(int key, void **param, t_map *map)
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

void	deal_key_helper_four(int key, void **param, t_map *map, t_node *beg)
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
		if (((beg->isoy + ((((map->ys - beg->isoy) * ZOOM_SPEED) / 100) * map->zoom)) + 0) < map->ys)
		{
			map->zoom += 1;
		}
		map->on = 1;
		draw_grid(param);
	}
}

void	deal_key_helper_three(int key, void **param, t_map *map)
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

void	deal_key_helper_two(int key, void **param, t_map *map)
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

void	deal_key_helper_one(int key, void **param, t_map *map)
{
	if (key == 53)
	{
		mlx_destroy_window(param[0], param[1]);
		free_last(map, param);
		exit (0);
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
		deal_key_helper_one(key, param, map);
	if (key == 126 || key == 125)
		deal_key_helper_two(key, param, map);
	if (key == 15)
		deal_key_helper_three(key, param, map);
	if (key == 69 || key == 78)
		deal_key_helper_four(key, param, map, beg);
	if (key == 47)
		deal_key_helper_five(key, param, map);
	if (key == 43 || key == 49)
		deal_key_helper_six(key, param, map);
	return (0);
}

void	get_coordenates_of_next_pixel(t_co *co, int *d, int *s, int *err)
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
	
void	create_node_b_new_colors(t_node *b, t_colo *colo, t_map *map)
{
	colo->red2 = 65 + map->color;
	colo->green2 = 50 + map->color;
	colo->blue2 = 0 + map->color;
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 1)))
	{
		colo->red2 = 220 + map->color;
		colo->green2 = 170 + map->color;
		colo->blue2 = 0 + map->color;
	}
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 2)))
	{
		colo->red2 = 255 + map->color;
		colo->green2 = 255 + map->color;
		colo->blue2 = 0 + map->color;
	}
	if (b->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 3)))
	{
		colo->red2 = 255 + map->color;
		colo->green2 = 255 + map->color;
		colo->blue2 = 200 + map->color;
	}
}	

void	create_node_a_new_colors(t_node *a, t_colo *colo, t_map *map)
{
	colo->red1 = 65 + map->color;
	colo->green1 = 50 + map->color;
	colo->blue1 = 0 + map->color;
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 1)))
	{
		colo->red1 = 220 + map->color;
		colo->green1 = 170 + map->color;
		colo->blue1 = 0 + map->color;
	}
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 2)))
	{
		colo->red1 = 255 + map->color;
		colo->green1 = 255 + map->color;
		colo->blue1 = 0 + map->color;
	}
	if (a->z >= (map->min_z + (((map->max_z - map->min_z) / 4) * 3)))
	{
		colo->red1 = 255 + map->color;
		colo->green1 = 255 + map->color;
		colo->blue1 = 200 + map->color;
	}
}

int		calc_current_color_bonus(int percent, t_node *a, t_node *b, void **param)
{
	t_colo	*colo;
	t_map	*map;
	int		ret;

	colo = (t_colo *)malloc(sizeof(t_colo) * 1);
	map = (t_map *)(param[3]);
	create_node_a_new_colors(a, colo, map);
	create_node_b_new_colors(b, colo, map);
	if (colo->red1 == colo->red2 && colo->green1 == colo->green2 && colo->blue1 == colo->blue2)
	{
		colo->curr_red = colo->red1;
		colo->curr_green = colo->green1;
		colo->curr_blue = colo->blue1; 
	}
	else
	{
		colo->curr_red = calculate_channel(percent, colo->red1, colo->red2); 
		colo->curr_green = calculate_channel(percent, colo->green1, colo->green2); 
		colo->curr_blue = calculate_channel(percent, colo->blue1, colo->blue2); 
	}
	colo->curr_red = 16711680 - ((255 - colo->curr_red) * 65536);
	colo->curr_green = (colo->curr_green * 65280) / 255;
	ret = colo->curr_red + colo->curr_green + colo->curr_blue;
	free(colo);
	return (ret);
}

int		calc_current_color_native(int percent, t_node *a, t_node *b)
{
	int		curr_red;
	int		curr_green;
	int		curr_blue;

	if (a->color.red == b->color.red && a->color.green == b->color.green\
		&& a->color.blue == b->color.blue)
	{
		curr_red =  a->color.red;
		curr_green = a->color.green;
		curr_blue = a->color.blue; 
	}
	else
	{
		curr_red = calculate_channel(percent, a->color.red, b->color.red); 
		curr_green = calculate_channel(percent, a->color.green, b->color.green); 
		curr_blue = calculate_channel(percent, a->color.blue, b->color.blue); 
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

void	free_arrays_int(int *d, int *s, int *err)
{
	free(d);
	free(s);
	free(err);
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
		percent = d[0] >= d[1] ? perc_calc(co->x0, co->x0c, co->x1c) : perc_calc(co->y0, co->y0c, co->y1c);  
		if (((t_map *)(param[3]))->on)
			color = ((t_map *)(param[3]))->color ? calc_current_color_bonus(percent, a, b, param)\
			: calc_current_color_native(percent, a, b);
		else
			color = 0;
		mlx_pixel_put(param[0], param[1], co->x0, co->y0, color);
		if (co->x0 == co->x1 && co->y0 == co->y1)
			break ;
		get_coordenates_of_next_pixel(co, d, s, err);
	}
	free_arrays_int(d, s, err);
}

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

void	store_x_and_y_coordenates_iso(t_node *a, t_node *b, void **param, t_co *co)
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
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 || co->x1 > map->win_wide || co->y0 < 0\
		   	|| co->y0 > map->win_heigh || co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	store_x_and_y_coordenates_plan(t_node *a, t_node *b, void **param, t_co *co)
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
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 || co->x1 > map->win_wide || co->y0 < 0\
		   	|| co->y0 > map->win_heigh || co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	store_x_and_y_coordenates_front(t_node *a, t_node *b, void **param, t_co *co)
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
	if (co->x0 < 0 || co->x0 > map->win_wide || co->x1 < 0 || co->x1 > map->win_wide || co->y0 < 0\
		   	|| co->y0 > map->win_heigh || co->y1 < 0 || co->y1 > map->win_heigh)
		if (map->win_heigh != 1440)
			increase_window(map, param, beg);
}

void	draw_cols(void **param, t_node *trav, t_map *map, t_co *co)
{
	t_node	*adv;
	
	adv = trav;
	while (trav)
	{
		while (adv->down)
		{
			map->proj == 1 ? store_x_and_y_coordenates_iso(adv, adv->down, param, co) : 0;
			map->proj == 2 ? store_x_and_y_coordenates_plan(adv, adv->down, param, co) : 0;
			map->proj == 3 ? store_x_and_y_coordenates_front(adv, adv->down, param, co) : 0;
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
			map->proj == 1 ? store_x_and_y_coordenates_iso(adv, adv->left, param, co) : 0;
			map->proj == 2 ? store_x_and_y_coordenates_plan(adv, adv->left, param, co) : 0;
			map->proj == 3 ? store_x_and_y_coordenates_front(adv, adv->left, param, co) : 0;
			draw_line(param, co, adv, adv->left);
			adv = adv->left;
		}
		trav = trav->down;
		adv = trav;
	}
}

void	draw_text_menu(void **param)
{
	mlx_string_put(param[0], param[1], 30, 30, 0xFFFFFF,  "View     : < and >");
	mlx_string_put(param[0], param[1], 30, 50, 0xFFFFFF,  "Altitud  : mouse scroll");
	mlx_string_put(param[0], param[1], 30, 70, 0xFFFFFF,  "Position : arrow keys");
	mlx_string_put(param[0], param[1], 30, 90, 0xFFFFFF,  "Zoom     : + and -");
	mlx_string_put(param[0], param[1], 30, 110, 0xFFFFFF, "Color    : space bar");
	mlx_string_put(param[0], param[1], 30, 130, 0xFFFFFF, "Reset    : R");
	mlx_string_put(param[0], param[1], 30, 150, 0xFFFFFF, "Exit     : esc");
}

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

t_node	*move_pointer_to_top_right_corner(t_node *trav)
{
	while (trav->up)
		trav = trav->up;
	while (trav->right)
		trav = trav->right;
	return (trav);
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

void	initialize_projection_helper(t_pro *p, t_map *map)
{
	p->isox = map->xs;
	p->isoy = map->ys;
	p->plax = map->xs;
	p->play = map->ys;
	p->frox = map->xs;
	p->froy = map->ys;
}

void	assign_helper(t_node *adv, t_pro *p, t_map *map)
{
	adv->isox = p->isox;
	adv->isoy = p->isoy;
	adv->plax = p->plax;
	adv->play = p->play;
	adv->frox = p->frox;
	adv->froy = p->froy;
	p->isox +=  map->opp;
	p->isoy -=  map->adj;
	p->plax += (map->opp * 1.2);
	p->frox += (map->opp * 1.2);
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

int		ft_atoi_hex(const char *str)
{
	int num;
	long result;
	
	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = *str - 48;
		else if (*str >= 'a' && *str <= 'f')
			num = (*str - 'a') + 10;
		else if (*str >= 'A' && *str <= 'F')
			num = (*str - 'A') + 10;
		else
			break ;
		result = (result * 16) + num;
		++str;
	}
	return ((int)result);
}

int		ft_is_hex_digit(int c)
{
	if (c && (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
		return (1);
	else
		return (0);
}


int		ft_strlen_hex(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_is_hex_digit(str[i]))
		++i;
	return (i);
}

void	copy_hex_in_channels_biarray(char *hex, char **channels)
{
	int		len;
	int		last;
	int		i;
	int		j;
	
	hex += 2;
	len = ft_strlen_hex(hex);
	last = len - 1;
	i = 2;
	j = 1;
	while (len--)
	{
		channels[i][j] = hex[last--];
		if (j) 
			--j;
		else
		{
			if (!i)
				break ;
			--i;
			j = 1;
		}
	}
}

void	initialize_channels_with_ceros(char **channels)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		channels[i] = ft_strnew(2);
		j = 0;
		while (j < 2)
			channels[i][j++] = '0';
		++i;
	}
}

void	assign_color_to_node(char *hex, t_node *beg)
{
	char	**channels;

	channels = ft_stranew(3);
	initialize_channels_with_ceros(channels);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		copy_hex_in_channels_biarray(hex, channels);
	beg->color.red = ft_atoi_hex(channels[0]);
	beg->color.green = ft_atoi_hex(channels[1]);
	beg->color.blue = ft_atoi_hex(channels[2]);
	free_array(channels);
}


void	assign_data_to_node(t_node *trav, char *data, t_map *map)
{
	char	**z_hex;
		
	z_hex = ft_strsplit(data, ',');
	trav->z = ft_atoi(z_hex[0]);
	trav->z > map->max_z ? map->max_z = trav->z : 0;
	trav->z < map->min_z ? map->min_z = trav->z : 0;
	if (z_hex[1])
	{
		assign_color_to_node(z_hex[1], trav);
	}
	free_array(z_hex);
}

t_node	*create_node(void)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	node->isox = 0;
	node->isoy = 0;
	node->plax = 0;
	node->play = 0;
	node->frox = 0;
	node->froy = 0;
	node->z = 0;
	node->color.red = 255;
	node->color.green = 255;
	node->color.blue = 255;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	return (node);
}

int		validate_quantity_of_data_packets(char **data, int *count)
{
	int		i;

	i = 0;
	while (data[i])
		++i;
	if (*count)
	{
	 	if (*count != i)
		{  
			free_array(data);
			return (0);
		}
	}
	else
		*count = i;
	return (1);
}

void	prepare_next_node(t_node *trav, char *data, t_map *map)
{
	trav->right = create_node();
	assign_data_to_node(trav->right, data, map);
	trav->right->left = trav;
}

t_node	*create_list(char *line, int *count, t_map *map)
{
	t_node	*beg;
	t_node	*trav;
	char	**data;
	char	**data_beg;
	
	if (!(validate_quantity_of_data_packets(data = ft_strsplit(line, ' ') , count)))
		return (NULL);
	beg = NULL;
	data_beg = data;
	if (*data)
	{
		beg = create_node();
		assign_data_to_node(beg, *data, map);
		++data;
		trav = beg;
		while (*data)
		{
			prepare_next_node(trav, *data, map);
			trav = trav->right;
			++data;
		}
	}
	free_array(data_beg);
	return (beg);
}

t_node	*create_structure_of_nodes(int fd, t_map *map)
{	
	int		*count;
	int		ret;
	char	*line;
	t_node	*prev;
	t_node	*trav;

	count = (int *)malloc(sizeof(int) * 1);
	*count = 0;
	prev = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(trav = create_list(line, count, map)))
		{
			close(fd);
			free(count);	
			return (NULL);
		}
		if (prev)
			connect_up(prev, trav);
		prev = trav;
		trav = trav->down;
	}
	close (fd);
	free(count);
	return (prev);
}

int		read_file(char **av)
{
	int		fd;
	
	if ((fd = open(av[1], O_RDONLY, 0)) == -1)
		print_error_and_exit(2);
	return (fd);
}

t_map	*initialize_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map) * 1);
	map->rows = 0;
	map->cols = 0;
	map->adj= 0;
	map->opp = 0;
	map->z = 0;
	map->x = 0;
	map->y = 0;
	map->on = 1;
	map->xs = 0;
	map->ys = 0;
	map->zoom = 0;
	map->proj = 1;
	map->win_heigh = 720;
	map->win_wide = 1080;
	map->max_z = 0;
	map->min_z = 0;
	map->color = 0;
	return (map);
}

void	build_wireframe(char **av)
{
	t_map		*map;
	t_node		*beg;
	
	map = initialize_map();
	if (!(beg = create_structure_of_nodes(read_file(av), map)))
	{
		free(map);
		print_error_and_exit(3);
	}
	get_rows_and_cols(beg, map);
	get_adjacent_and_opposite(map);
	get_x_y_start(map);
	assign_coordenates(beg, map);
	beg = move_pointer_to_top_right_corner(beg);
	open_graphic_interface(beg, map);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		build_wireframe(av);
	else
		print_error_and_exit(1);
	return (0);
}
