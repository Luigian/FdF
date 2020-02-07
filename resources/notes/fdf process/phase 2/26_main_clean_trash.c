/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/07 19:16:48 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

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
			trav->y = trav->y - (trav->z * (dir ? Z_SPEED : (-Z_SPEED))); 
			trav = trav->left;
		}
		trav = beg->down;
	}
}

int		deal_key(int key, void **param)
{
	t_node	*beg;
	t_map	*map;
	
	beg = (t_node *)(param[2]);
	map = (t_map *)(param[3]);
	
	if (key == 53)
		exit (0);
	if (key == 69)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->z -= 1;
		draw_grid(param);
	}
	if (key == 78)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->z += 1;
		draw_grid(param);
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
	if (key == 15)
	{
		map->on = 0;
		draw_grid(param);
		map->on = 1;
		map->z = 0;
		map->x = 0;
		map->y = 0;
		draw_grid(param);
	}
	if (key == 91)
	{
		map->on = 0;
		draw_grid(param);
//		map->i_x = 
		
//		map->on = 1;
//		map->z = 0;
//		map->x = 0;
//		map->y = 0;
//		draw_grid(param);
	}
	return (0);
}

void	get_coordenates_of_next_pixel(int *xy, int *d, int *s, int *err)
{		
	err[1] = err[0];
	if (err[1] > -(d[0]))
	{
		err[0] -= d[1];
		xy[0] += s[0];
	}
	if (err[1] < d[1]) 
	{
		err[0] += d[0];
		xy[1] += s[1];
	}
}

int		calculate_channel(int percent, int a_color, int b_color)
{	
	int		result;

	result = 0;
	result = a_color - (((a_color - b_color) * percent) / 100);
	return (result);
}

int		calculate_current_color(int percent, t_node *a, t_node *b)
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
	return ((placement * 100) / distance);
}

void	get_draw_metrics(int *xy, int *d, int *s, int *err)
{
	d[0] = abs(xy[2] - xy[0]);
	d[1] = abs(xy[3] - xy[1]);
	s[0] = xy[0] < xy[2] ? 1 : -1;
	s[1] = xy[1] < xy[3] ? 1 : -1; 
	err[0] = (d[0] > d[1] ? d[0] : -(d[1])) / 2;
}

void	draw_line(void **param, int *xy, t_node *a, t_node *b)
{
	int		*d;
	int		*s;
	int		*err;
	int		color;
	int		percent;
	t_map	*map;
	
	map = (t_map *)(param[3]);
	d = (int *)malloc(sizeof(int) * 2);
	s = (int *)malloc(sizeof(int) * 2);
	err = (int *)malloc(sizeof(int) * 2);
	get_draw_metrics(xy, d, s, err);
	while (1)
	{
		percent = d[0] >= d[1] ? perc_calc(xy[0], xy[4], xy[6]) : perc_calc(xy[1], xy[5], xy[7]);  
		color = map->on ? calculate_current_color(percent, a, b) : 0;
		mlx_pixel_put(param[0], param[1], xy[0], xy[1], color);
		if (xy[0] == xy[2] && xy[1] == xy[3])
			break ;
		get_coordenates_of_next_pixel(xy, d, s, err);
	}
}

int		*store_x_and_y_coordenates(t_node *a, t_node *b, void **param)
{
	int		*xy;
	t_map	*map;

	xy = (int *)malloc(sizeof(int) * 8);
	map = (t_map *)(param[3]);
	xy[0] = a->x + (map->x * X_SPEED);
	xy[1] = (a->y + (a->z * (map->z * Z_SPEED))) + (map->y * X_SPEED);
	xy[2] = b->x + (map->x * X_SPEED);
	xy[3] = (b->y + (b->z * (map->z * Z_SPEED))) + (map->y * X_SPEED);
	xy[4] = a->x + (map->x * X_SPEED);
	xy[5] = (a->y + (a->z * (map->z * Z_SPEED))) + (map->y * X_SPEED);
	xy[6] = b->x + (map->x * X_SPEED);
	xy[7] = (b->y + (b->z * (map->z * Z_SPEED))) + (map->y * X_SPEED);
	///////////////// proportion
/*	xy[0] = 
	xy[1] = 
	xy[2] = 
	xy[3] = 
	xy[4] = 
	xy[5] = 
	xy[6] = 
	xy[7] = */
	return (xy);
}

void	draw_cols(void **param, t_node *trav)
{
	t_node	*adv;
	int		*xy;
	
	adv = trav;
	while (trav)
	{
		while (adv->down)
		{
			xy = store_x_and_y_coordenates(adv, adv->down, param);
			draw_line(param, xy, adv, adv->down);
			adv = adv->down;
		}
		trav = trav->left;
		adv = trav;
	}
}

void	draw_rows(void **param, t_node *trav)
{
	t_node	*adv;
	int		*xy;
	
	adv = trav;
	while (trav)
	{
		while (adv->left)
		{
			xy = store_x_and_y_coordenates(adv, adv->left, param);
			draw_line(param, xy, adv, adv->left);
			adv = adv->left;
		}
		trav = trav->down;
		adv = trav;
	}
}

void	draw_grid(void **param)
{
	t_node	*trav;
	
	trav = (t_node *)(param[2]);
	draw_rows(param, trav);
	draw_cols(param, trav);
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
	
	printf("start graphic interface\n");			////////////
	printf("beg x : %f\n", beg->x);					///////////
	printf("beg y : %f\n", beg->y);					///////////
	param = (void **)malloc(sizeof(void *) * 4);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDE, WIN_HEIGH, "fdf");
	param[0] = mlx_ptr;
	param[1] = win_ptr;	
	param[2] = beg;
	param[3] = map;
	draw_grid(param);
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_loop(mlx_ptr);
}

void	assign_coordenates(t_node *trav, t_map *map, double x, double y)
{
	t_node	*start;
	t_node	*adv;

	start = trav;
	adv = trav;
	while (trav)
	{
		while (adv)
		{
			adv->x = x;
			adv->y = y;
			x = x + map->opp;
		   	y = y - map->adj;
			adv = adv->right;
		}
		x = trav->x - map->opp;
		y = trav->y - map->adj;
		trav = trav->up;
		adv = trav;
	}
}

void	get_x_y_start(t_map *map)
{
	map->xs = (WIN_WIDE / 2) - ((map->cols - map->rows) * (map->opp / 2));
	map->ys = WIN_HEIGH - (WIN_WIDE / 16);
}

void	get_adjacent_and_opposite(t_map *map)
{
	int			sides;

	sides = (map->rows - 1) + (map->cols - 1);
	map->adj = (WIN_HEIGH - (WIN_WIDE / 8)) / sides;
	map->opp = map->adj * (tan(60 * 3.1416 / 180));
	while (((map->opp = map->adj * (tan(60 * 3.1416 / 180))) * sides) >\
		(WIN_WIDE - (WIN_WIDE / 8)))
		--map->adj;
	printf("map->adj: %f\n", map->adj);		////////////////
	printf("map->opp: %f\n", map->opp);		////////////////
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
}

void	assign_data_to_node(t_node *trav, char *data)
{
	char	**z_hex;
		
	z_hex = ft_strsplit(data, ',');
	trav->z = ft_atoi(z_hex[0]);
	if (z_hex[1])
		assign_color_to_node(z_hex[1], trav);
}

t_node	*create_node(void)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	node->x = 0;
	node->y = 0;
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
		   return (0);
	}
	else
		*count = i;
	return (1);
}

t_node	*create_list(char *line, int *count)
{
	t_node	*beg;
	t_node	*trav;
	char	**data;
	
	data = ft_strsplit(line, ' ');
	if (!(validate_quantity_of_data_packets(data, count)))
		return (NULL);
	beg = NULL;
	if (*data)
	{
		beg = create_node();
		assign_data_to_node(beg, *data);
		++data;
		trav = beg;
		while (*data)
		{
			trav->right = create_node();
			assign_data_to_node(trav->right, *data);
			trav->right->left = trav;
			trav = trav->right;
			++data;
		}
	}
	return (beg);
}

t_node	*create_structure_of_nodes(int fd)
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
		if (!(trav = create_list(line, count)))
			return (NULL);
		if (prev)
			connect_up(prev, trav);
		prev = trav;
		trav = trav->down;
	}
	return (prev);
}

int		read_file(char **av)
{
	int		fd;
	
	if ((fd = open(av[1], O_RDONLY, 0)) == -1)
		print_error_and_exit(2);
	return (fd);
}

t_map	*initialize_map()
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
	return (map);
}

void	build_wireframe(char **av)
{
	t_map		*map;
	t_node		*beg;
	if (!(beg = create_structure_of_nodes(read_file(av))))
		print_error_and_exit(3);
	map = initialize_map();
	get_rows_and_cols(beg, map);
	get_adjacent_and_opposite(map);
	get_x_y_start(map);
	assign_coordenates(beg, map, map->xs, map->ys);
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