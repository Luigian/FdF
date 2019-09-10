/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/01 09:56:06 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	node->left = NULL;
	node->right = NULL;
	node->down = NULL;
	return (node);
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
		result = (result * 16) + num;
		++str;
	}
	return ((int)result);
}

void	assign_colors(char *line, t_node *beg)
{
	int		i;
	int		j;
	int		n;
	char 	red[3];
	char 	green[3];
	char 	blue[3];

	i = 3;
	j = 0;
	n = 2;
	while (n--)
		red[j++] = line[i++];
	red[j] = '\0';
	j = 0;
	n = 2;
	while (n--)
		green[j++] = line[i++];
	green[j] = '\0';
	j = 0;
	n = 2;
	while (n--)
		blue[j++] = line[i++];
	blue[j] = '\0';
	beg->color.red = ft_atoi_hex(red);
	beg->color.green = ft_atoi_hex(green);
	beg->color.blue = ft_atoi_hex(blue);
}

t_node	*create_list(char *line, int *zaxis)
{
	t_node	*beg;
	t_node	*trav;

	beg = create_node();
	beg->z = atoi(line);
	beg->z > zaxis[0] ? zaxis[0] = beg->z : 0;
	beg->z < zaxis[1] ? zaxis[1] = beg->z : 0;
	while (*line && *line != ' ' && *line != ',')
		++line;
	if (*line == ',')
		assign_colors(line, beg);
	while (*line && *line != ' ')
		++line;	
	trav = beg;
	while (*line)
	{
		if (*line != ' ')
		{
			trav->right = create_node();
			trav->right->z = atoi(line);
			trav->right->z > zaxis[0] ? zaxis[0] = trav->right->z : 0;
			trav->right->z < zaxis[1] ? zaxis[1] = trav->right->z : 0;
			while (*line && *line != ' ' && *line != ',')
				++line;	
			if (*line == ',')
				assign_colors(line, trav->right);
			while (*line && *line != ' ')
				++line;
			trav = trav->right;
		}
		else if (*line == ' ')			
			++line;
	}
	return (beg);
}

void	connect_left(t_node *trav_1, t_node *trav_2)
{
	trav_2->left = trav_1;
	while (trav_2->right)
	{
		trav_1 = trav_1->right;
		trav_2 = trav_2->right;
		trav_2->left = trav_1;
	}
}

t_node	*create_node_structure(char **lines, int lines_rows, int *zaxis)
{	
	t_node	*beg;
	t_node	*trav;

	int		i;
	
	i = 0;
	beg = create_list(lines[i], zaxis);
	trav = beg;
	i++;
	while (i < lines_rows)
	{
		trav->down = create_list(lines[i], zaxis);
		connect_left(trav, trav->down);
		trav = trav->down;
		++i;
	}
	return (trav);
}

int		struct_cols_counter(t_node *trav)
{
	int		struct_cols;

	struct_cols = 0;
	while (trav)
	{
		++struct_cols;
		trav = trav->right;
	}
	return (struct_cols);
}

int		*pixel_metrics_calculator(int lines_rows, int struct_cols, int *zaxis)
{
	int		*pixels;
	int		wide;
	int		heigh;
	int		adjacent;
	int		opposite;

	pixels = (int *)malloc(sizeof(int) * 4);
	wide = 28 * (struct_cols > lines_rows ? struct_cols : lines_rows);
	heigh = (14 * lines_rows) + ((struct_cols - lines_rows) * 7);
	opposite = 14;
	adjacent = opposite / 2;
	heigh = heigh + (zaxis[0] * ((adjacent * 3) - 1));
	heigh = heigh + ((zaxis[1] * -1) * ((adjacent * 3) - 1));
	pixels[0] = wide;
   	pixels[1] = heigh;
	pixels[2] = adjacent;
	pixels[3] = opposite;
	return (pixels);
}

void	assign_coordenates(t_node *trav, int x, int y, int adj, int opp)
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
			adv->y = y - (adv->z * ((adj * 3) - 1));
			x = x + opp;
		   	y = y - adj;
//			printf("-------------------\n");	///////////////////////////////////
//			printf("red: %d\n", adv->color.red);	//////////////////////////////////////
//			printf("green: %d\n", adv->color.green);	///////////////////////////////////
//			printf("blue: %d\n", adv->color.blue);	///////////////////////////////////
			adv = adv->right;
		}
		x = trav->x - opp;
		y = (trav->y + (trav->z * ((adj * 3) - 1))) - adj;
		trav = trav->left;
		adv = trav;
	}
//	printf("---------------------------------");	///////////////////////////////////
}

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
//	printf("percentage: %d\n", percentage);		/////////////////////////////////////////
	if ((red = adv->color.red - adv_second->color.red) < 0)
	{
		red *= -1;
		red = adv->color.red + ((red * percentage) / 100);
	}
	else
		red = adv->color.red - ((red * percentage) / 100);
//	printf("redhex: %d\n", red);	//////////////////////////////////
	red = 16711680 - ((255 - red) * 65536);
//	printf("red: %d\n", red);	///////////////////////////////////////////////
	if ((green = adv->color.green - adv_second->color.green) < 0)
	{
		green *= -1;
		green = adv->color.green + ((green * percentage) / 100);
	}
	else
		green = adv->color.green - ((green * percentage) / 100);
//	printf("greenhex: %d\n", green);	////////////////////////////
	green = (green * 65280) / 255;
//	printf("green: %d\n", green);	//////////////////////
	if ((blue = adv->color.blue - adv_second->color.blue) < 0)
	{
		blue *= -1;
		blue = adv->color.blue + ((blue * percentage) / 100);
	}
	else
		blue = adv->color.blue - ((blue * percentage) / 100);
//	printf("bluehex: %d\n", blue);	//////////////////
//	printf("blue: %d\n", blue);	///////////////////
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
//		printf("color: %d\n", color);				/////////////////////////////////////////////
//		printf("------------------------------");	///////////////////////////////////////////
		
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

	start = trav;
	adv = trav;
	while (trav)
	{
		while (adv->right)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->right);
			adv = adv->right;
		}
		trav = trav->left;
		adv = trav;
	}
	trav = start;
	adv = trav;
	while (trav)
	{
		while (adv->left)
		{
			draw_line(mlx_ptr, win_ptr, adv, adv->left);
			adv = adv->left;
		}
		trav = trav->right;
		adv = trav;
	}
}

int		main(void)
{
	t_node	*beg;
//	char	*lines[] = { "0 0,0xFFFF00 0,0xFF0000", "0 0,0xFFFF00 0,0xFF0000", "0 0,0xFFFF00 0,0xFF0000" };
//	char	*lines[] = { "0,0xFFFFFF 5,0xFF0000" };
//	char	*lines[] = { "0,0x0000FF 5,0x000000" };
//	char	*lines[] = { "0 0,0xFFFF00 0,0xFF0000", "0 0,0xFFFF00 0,0xFF0000" };
//	char	*lines[] = { "0,0xFFFFFF 0,0xFF0000", "0 0" };
//	char	*lines[] = { "0,0xFF0000", "0" };
	
/*	char	*lines[] = { "0 0 0 0 0 0 0 0 0 0",
	   					"0 10 10 10 10 10 10 10 10 0",
   						"0 10 20,0xFF0000 15,0xFF0000 12 15,0xFF0000 17,0xFF0000 20,0xFF0000 10 0",
						"0 10 15,0xFF0000 10 12 15,0xFF0000 15,0xFF0000 15,0xFF0000 10 0",
						"0 5 15,0xFF0000 10 12 15,0xFF0000 15,0xFF0000 13 10 0",
						"0 5 10 5 7 12 12 12 10 0",
						"0 5 7 1 2 7 5 5 7 0",
						"0 3 0 0 1 2 2 2 5 0",
						"0 1 0 0 0 0 0 0 3 0",
						"0 0 0 0 0 0 0 0 0 0" };
*//*	
	char	*lines[] = { "1 0 0 -1 -1 0 1 1 0 0",
	   					"-1 0 0 0 1 0 0 0 0 0",
   						"-1 1 0 0 -1 1 0 0 0 1",
						"1 -1 0 1 1 -1 0 0 -1 0",
						"1 -1 -1 0 -1 0 0 0 -1 1",
						"-1 1 0 1 1 0 1 0 0 0",
						"0 -1 -1 0 0 1 0 0 0 1",
						"0 0 0 0 1 0 -1 0 0 0",
						"-1 -1 0 1 -1 0 1 0 0 1",
						"0 0 1 -1 0 -1 0 0 0 0" };
	*/
	char	*lines[] = {"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0",
	   					"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0",
   						"0  0 10,0xEB8E2F  10,0xEB8E2F   0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0",
						"0  0 10,0xEB8E2F  10,0xEB8E2F 0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0 10,0xEB8E2F  10,0xEB8E2F   0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0",
						"0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0",
						"0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0",
						"0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0", 
						"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0" };
/*

	char	*lines[] = {"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0",
	   					"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0",
   						"0  0 10,0xFF0000  10,0xFF0000   0  0 10,0xFF0000  10,0xFF0000   0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0",
						"0  0 10,0xFF0000  10,0xFF0000 0  0 10,0xFF0000  10,0xFF0000   0  0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0 10,0xFF0000  10,0xFF0000   0  0 10,0xFF0000  10,0xFF0000   0  0  0  0  0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0 10,0xFF0000  10,0xFF0000  10,0xFF0000  10,0xFF0000  10,0xFF0000  10,0xFF0000   0  0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0  0",
						"0  0  0 10,0xFF0000  10,0xFF0000  10,0xFF0000  10,0xFF0000  10,0xFF0000   0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0",
						"0  0  0  0  0  0 10,0xFF0000  10,0xFF0000   0  0  0 10,0xEB8E2F  10,0xEB8E2F   0  0  0  0  0  0",
						"0  0  0  0  0  0 10,0xFF0000  10,0xFF0000   0  0  0 10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F  10,0xEB8E2F   0  0",
						"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0", 
						"0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0" };
*/
//	char	*lines[] = { "0,0xEB8E2F", "0" };

	int		lines_rows = 11;
	int		struct_cols;
	int		*pixels;
	void	*mlx_ptr;
	void	*win_ptr;
	int		*zaxis;
	
	zaxis = (int *)malloc(sizeof(int) * 2);
	zaxis[0] = 0;
	zaxis[1] = 0;
	beg = create_node_structure(lines, lines_rows, zaxis);
	struct_cols = struct_cols_counter(beg);
	pixels = pixel_metrics_calculator(lines_rows, struct_cols, zaxis);
	assign_coordenates(beg, pixels[0] / 2, (pixels[1] - ((zaxis[1] * -1) * ((pixels[2] * 3) - 1)))\
		- 1, pixels[2], pixels[3]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, pixels[0], pixels[1], "fils de fer");
	draw_grid(mlx_ptr, win_ptr, beg);
	mlx_loop(mlx_ptr);
}
