/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/06 16:08:26 by lusanche         ###   ########.fr       */
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

void	draw_grid(void *mlx_ptr, void * win_ptr, t_node *trav);

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

void	set_del_value(void **param, int code)
{
	t_node		*trav;
	t_node		*beg;

	trav =  (t_node *)(param[2]);
	while (trav)
	{
		beg = trav;
		while (trav)
		{
			trav->del = code; 
			trav = trav->left;
		}
		trav = beg->down;
	}
}

int		deal_key(int key, void **param)
{
	t_node	*beg;
	
	if (key == 53)
		exit (0);
	if (key == 126)
	{
		beg = (t_node *)(param[2]);
		beg->del = 1;
		draw_grid(param[0], param[1], beg);
		
		increase_decrease_y_coordenate(param, 1);
		beg->del = 0;
		draw_grid(param[0], param[1], beg);
	}
/*	if (key == 125)
	{
		set_del_value(param, 1);
		draw_grid(param[0], param[1], (t_node *)(param[2]));
		increase_decrease_y_coordenate(param, 0);
		set_del_value(param, 0);
		draw_grid(param[0], param[1], (t_node *)(param[2]));
	}*/
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

int		*store_x_and_y_coordenates(t_node *a, t_node *b)
{
	int		*xy;
	
	xy = (int *)malloc(sizeof(int) * 4);
	xy[0] = a->x;
	xy[1] = a->y;
	xy[2] = b->x;
	xy[3] = b->y;
	return (xy);
}

void	draw_line(void *mlx_ptr, void *win_ptr, t_node *a, t_node *b)
{
	int		*xy;
	int		*d;
	int		*s;
	int		*err;
	int		color;
	int		percent;
	
	xy = store_x_and_y_coordenates(a, b);
	d = (int *)malloc(sizeof(int) * 2);
	s = (int *)malloc(sizeof(int) * 2);
	err = (int *)malloc(sizeof(int) * 2);
	get_draw_metrics(xy, d, s, err);
	while (1)
	{
		percent = d[0] >= d[1] ? perc_calc(xy[0], a->x, b->x) : perc_calc(xy[1], a->y, b->y);  
		color = a->del ? 0 : calculate_current_color(percent, a, b);
//		color = calculate_current_color(percent, a, b);
		mlx_pixel_put(mlx_ptr, win_ptr, xy[0], xy[1], color);
		if (xy[0] == xy[2] && xy[1] == xy[3])
			break ;
		get_coordenates_of_next_pixel(xy, d, s, err);
	}
}

void	draw_cols(void *mlx_ptr, void *win_ptr, t_node *trav, t_node *adv)
{
	while (trav)
	{
		while (adv->down)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->down);
			adv->down->del = adv->del ? 1 : 0;
			adv = adv->down;
		}
		if (trav->left)
			trav->left->del = trav->del ? 1 : 0;
		trav = trav->left;
		adv = trav;
	}
}

void	draw_rows(void *mlx_ptr, void *win_ptr, t_node *trav, t_node *adv)
{
	while (trav)
	{
		while (adv->left)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->left);
//			if (adv->down)
//				draw_line(mlx_ptr, win_ptr, adv, adv->left->down);
			adv->left->del = adv->del ? 1 : 0;
			adv = adv->left;
		}
		if (trav->down)
			trav->down->del = trav->del ? 1 : 0;
		trav = trav->down;
		adv = trav;
	}
}


void	draw_grid(void *mlx_ptr, void * win_ptr, t_node *trav)
{
	t_node	*adv;

	adv = trav;
	draw_rows(mlx_ptr, win_ptr, trav, adv);
	draw_cols(mlx_ptr, win_ptr, trav, adv);
}

t_node	*move_pointer_to_top_right_corner(t_node *trav)
{
	while (trav->up)
		trav = trav->up;
	while (trav->right)
		trav = trav->right;
	return (trav);
}

void	open_graphic_interface(t_node *beg)
{
	void		**param;
	void		*mlx_ptr;
	void		*win_ptr;
	
	printf("start graphic interface\n");			////////////
	printf("beg x : %f\n", beg->x);					///////////
	printf("beg y : %f\n", beg->y);					///////////
	param = (void **)malloc(sizeof(void *) * 3);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDE, WIN_HEIGH, "fdf");
	param[0] = mlx_ptr;
	param[1] = win_ptr;	
	param[2] = beg;
	draw_grid(mlx_ptr, win_ptr, beg);
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_loop(mlx_ptr);
}

void	assign_coordenates(t_node *trav, double x, double y, double *adj_opp)
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
//			adv->y = y - (adv->z * ((adj * 3) - (adj / 7)));
			x = x + adj_opp[1];
		   	y = y - adj_opp[0];
			adv = adv->right;
		}
		x = trav->x - adj_opp[1];
		y = trav->y - adj_opp[0];
//		y = (trav->y /*+ (trav->z * ((adj * 3) - (adj / 7))))*/ - adj;
		trav = trav->up;
		adv = trav;
	}
}

int		get_y_start(void)
{
	return (WIN_HEIGH - (WIN_WIDE / 16));
}

int		get_x_start(int *rows_cols, double opp)
{
	int		start;

	start = WIN_WIDE / 2;
	return (start - ((rows_cols[1] - rows_cols[0]) * (opp / 2)));
}

double		*get_adjacent_and_opposite(int *rows_cols)
{
	int			sides;
	double		adj;
	double		opp;
	double		*adj_opp;

	sides = (rows_cols[0] - 1) + (rows_cols[1] - 1);
	adj = (WIN_HEIGH - (WIN_WIDE / 8)) / sides;
	opp = adj * (tan(60 * 3.1416 / 180));
	while (((opp = adj * (tan(60 * 3.1416 / 180))) * sides) > (WIN_WIDE - (WIN_WIDE / 8)))
		--adj;
	adj_opp = (double *)malloc(sizeof(double) * 2);
	adj_opp[0] = adj;
   	adj_opp[1] = opp;
	printf("adj: %f\n", adj);		////////////////
	printf("opp: %f\n", opp);		////////////////
	return (adj_opp);
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

int		*get_rows_and_cols(t_node *beg)
{
	int		*rows_cols_ret;
	int		rows;
	int		cols;
	
	rows = struct_rows_counter(beg);
	cols = struct_cols_counter(beg);
	rows_cols_ret = (int *)malloc(sizeof(int) * 2);
	rows_cols_ret[0] = rows;
	rows_cols_ret[1] = cols;
	return (rows_cols_ret);
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

void	assign_data_to_node(t_node *trav, char *data/*, int *zaxis*/)
{
	char	**z_hex;
		
	z_hex = ft_strsplit(data, ',');
	trav->z = ft_atoi(z_hex[0]);
//	trav->z > zaxis[0] ? zaxis[0] = trav->z : 0;
//	trav->z < zaxis[1] ? zaxis[1] = trav->z : 0;
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
	node->del = 0;
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

t_node	*create_list(char *line/*, int *zaxis*/, int *count)
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
		assign_data_to_node(beg, *data/*, zaxis*/);
		++data;
		trav = beg;
		while (*data)
		{
			trav->right = create_node();
			assign_data_to_node(trav->right, *data/*, zaxis*/);
			trav->right->left = trav;
			trav = trav->right;
			++data;
		}
	}
	return (beg);
}

t_node	*create_structure_of_nodes(int fd/*, int *zaxis*/)
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
		if (!(trav = create_list(line/*, zaxis*/, count)))
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

void	build_wireframe(char **av)
{
	t_node		*beg;
	int			*rows_cols;
	double		*adj_opp;
//	int			*zaxis;						////////
	
//	zaxis = (int *)malloc(sizeof(int) * 2);	////////
//	zaxis[0] = 0;							////////
//	zaxis[1] = 0;							////////	
	if (!(beg = create_structure_of_nodes(read_file(av)/*, zaxis*/)))
		print_error_and_exit(3);
	rows_cols = get_rows_and_cols(beg);
	adj_opp = get_adjacent_and_opposite(rows_cols);
	assign_coordenates(beg, get_x_start(rows_cols, adj_opp[1]), get_y_start(), adj_opp);
	beg = move_pointer_to_top_right_corner(beg);
	open_graphic_interface(beg);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		build_wireframe(av);
	else
		print_error_and_exit(1);
	return (0);
}
