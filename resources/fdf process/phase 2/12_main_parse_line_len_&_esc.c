/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/04 19:58:02 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <math.h>

int		percent(int start, int end, int current)
{
    int		placement;
    int		distance;

	if ((distance = end - start) < 0)
		distance *= -1;
	if ((placement = current - start) < 0)
		placement *= -1;
	return ((placement * 100) / distance);
}

int		calculate_color(int dx, int dy, int x0, int y0, t_node *adv, t_node *adv_second)
{
	int		percentage;
	int		red;
	int		green;
	int		blue;

	if (adv->color.red == adv_second->color.red && adv->color.green == adv_second->color.green\
		&& adv->color.blue == adv_second->color.blue)
	{
		red = adv->color.red;
		green = adv->color.green;
		red = 16711680 - ((255 - red) * 65536);
		green = (green * 65280) / 255;
		return (red + green + adv->color.blue);
	}
	if (dx >= dy)
		percentage = percent(adv->x, adv_second->x, x0);
	else
		percentage = percent(adv->y, adv_second->y, y0);
	if ((red = adv->color.red - adv_second->color.red) < 0)
	{
		red *= -1;
		red = adv->color.red + ((red * percentage) / 100);
	}
	else
		red = adv->color.red - ((red * percentage) / 100);
	red = 16711680 - ((255 - red) * 65536);
	if ((green = adv->color.green - adv_second->color.green) < 0)
	{
		green *= -1;
		green = adv->color.green + ((green * percentage) / 100);
	}
	else
		green = adv->color.green - ((green * percentage) / 100);
	green = (green * 65280) / 255;
	if ((blue = adv->color.blue - adv_second->color.blue) < 0)
	{
		blue *= -1;
		blue = adv->color.blue + ((blue * percentage) / 100);
	}
	else
		blue = adv->color.blue - ((blue * percentage) / 100);
	return (red + green + blue);
}

void	draw_line(void *mlx_ptr, void *win_ptr, t_node *adv, t_node *adv_second)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		color;
	
	x0 = adv->x;
	y0 = adv->y;
	x1 = adv_second->x;
	y1 = adv_second->y;	
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1; 
	err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		color = calculate_color(dx, dy, x0, y0, adv, adv_second);
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
		if (x0 == x1 && y0 == y1) 
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
	   	}
		if (e2 < dy) 
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_grid(void *mlx_ptr, void * win_ptr, t_node *trav)
{
	t_node	*start;
	t_node	*adv;

	while (trav->up)
		trav = trav->up;
	while (trav->right)
		trav = trav->right;
	start = trav;
	adv = trav;
	while (trav)
	{
		while (adv->left)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->left);
//			if (adv->down)
//				draw_line(mlx_ptr, win_ptr, adv, adv->left->down);
			adv = adv->left;
		}
		trav = trav->down;
		adv = trav;
	}
	trav = start;
	adv = trav;
	while (trav)
	{
		while (adv->down)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->down);
			adv = adv->down;
		}
		trav = trav->left;
		adv = trav;
	}
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

double		*adjacent_opposite_calculator(int rows, int cols/*, int *zaxis*/)
{
	int			sides;
	double		*adj_opp;
	double		adj;
	double		opp;

	sides = (rows - 1) + (cols - 1);
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

int		ft_is_hexa_digit(int c)
{
	if (c && (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
		return (1);
	else
		return (0);
}

int		ft_strlen_hexa(char *str)
{
	int i;

	i = 2;
	while (str[i] && ft_is_hexa_digit(str[i]))
		++i;
	return (i);
}

void	copy_hexa_in_biarray(char *data, char **channels)
{
	int		len;
	int		last;
	int		i;
	int		j;
	
	len = ft_strlen_hexa(data);	
	last = len - 1;
	i = 2;
	j = 1;
	while (len--)
	{
		channels[i][j] = data[last--];
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

void	initialize_biarray(char **channels, char c)
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
			channels[i][j++] = c;
		++i;
	}
}

void	assign_color_to_node(char *data, t_node *beg)
{
	char	**channels;

	channels = ft_stranew(3);
	initialize_biarray(channels, '0');
	if (data[0] == '0' && (data[1] == 'x' || data[1] == 'X'))
	{
		data += 2;
		copy_hexa_in_biarray(data, channels);
	}
	beg->color.red = ft_atoi_hex(channels[0]);
	beg->color.green = ft_atoi_hex(channels[1]);
	beg->color.blue = ft_atoi_hex(channels[2]);
}

void	assign_data_to_node(t_node *trav, char *packet, int *zaxis)
{
	char	**data;
		
	data = ft_strsplit(packet, ',');
	trav->z = ft_atoi(*data);
	trav->z > zaxis[0] ? zaxis[0] = trav->z : 0;
	trav->z < zaxis[1] ? zaxis[1] = trav->z : 0;
	++data;
	if (*data)
		assign_color_to_node(*data, trav);
}

t_node	*create_node()
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

int		validate_quantity_of_packets(char **packets, int *count)
{
	int		i;

	i = 0;
	
	while (packets[i])
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

t_node	*create_list(char *line, int *zaxis, int *count)
{
	t_node	*beg;
	t_node	*trav;
	char	**packets;
	
	packets = ft_strsplit(line, ' ');
	if (!(validate_quantity_of_packets(packets, count)))
		return (NULL);
	beg = NULL;
	if (*packets)
	{
		beg = create_node();
		assign_data_to_node(beg, *packets, zaxis);
		++packets;
		trav = beg;
		while (*packets)
		{
			trav->right = create_node();
			assign_data_to_node(trav->right, *packets, zaxis);
			trav->right->left = trav;
			trav = trav->right;
			++packets;
		}
	}
	return (beg);
}

void	print_error_message(int code, char *av)
{
	if (code == 1)
		write(1, "Usage : ./fdf <filename>\n", 25);
	else if (code == 2)
		write(1, "Found wrong line length. Exiting.\n", 34);
	else if (code == 3)
	{
		write(1, "No file ", 8);
		ft_putendl(av);
	}
}

t_node	*create_structure_of_nodes(char **av, int *zaxis)
{	
	t_node	*prev;
	t_node	*trav;
	int		fd;
	char	*line;
	int		ret;
	int		*count;

	prev = NULL;
	if ((fd = open(av[1], O_RDONLY, 0)) == -1)
	{
		print_error_message(3, av[1]);
		return (NULL);
	}
	count = (int *)malloc(sizeof(int) * 1);
	*count = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(trav = create_list(line, zaxis, count)))
		{
			print_error_message(2, "");
			return (NULL);
		}
		if (prev)
			connect_up(prev, trav);
		prev = trav;
		trav = trav->down;
	}
	return (prev);
}

int		get_y_start()
{
	return (WIN_HEIGH - (WIN_WIDE / 16));
}

int		get_x_start(int rows, int cols, double opp)
{
	int		start;

	start = WIN_WIDE / 2;
	return (start - ((cols - rows) * (opp / 2)));
}

int		deal_key(int key, void *param)
{
	param = 0;
	if (key == 53)
		exit (0);
	return (0);
}

int		main(int ac, char **av)
{
	t_node		*beg;
	int			rows;
	int			cols;
	double		*adj_opp;
	void		*mlx_ptr;
	void		*win_ptr;
	int			*zaxis;
	
	if (ac != 2)
	{
		print_error_message(1, "");
		exit(0);
	}
	zaxis = (int *)malloc(sizeof(int) * 2);
	zaxis[0] = 0;
	zaxis[1] = 0;
	if (!(beg = create_structure_of_nodes(av, zaxis)))
		exit (0);
	rows = struct_rows_counter(beg);
	cols = struct_cols_counter(beg);
	adj_opp = adjacent_opposite_calculator(rows, cols/*, zaxis*/);
	assign_coordenates(beg, get_x_start(rows, cols, adj_opp[1]), get_y_start(), adj_opp);
	printf("end\n");
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDE, WIN_HEIGH, "fdf");
	draw_grid(mlx_ptr, win_ptr, beg);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
