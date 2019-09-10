/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/22 15:41:22 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

typedef struct	s_node
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*down;
}					t_node;

t_node	*create_node()
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	node->x = 0;
	node->y = 0;
	node->z = 0;
	node->color = 0xFFFFFF;
	node->left = NULL;
	node->right = NULL;
	node->down = NULL;
	return (node);
}

t_node	*create_list(char *line)
{
	t_node	*beg;
	t_node	*trav;

	beg = create_node();
	beg->z = atoi(line);
	while (*line && *line != ' ')
		++line;
	trav = beg;
	while (*line)
	{
		if (*line != ' ')
		{
			trav->right = create_node();
			trav->right->z = atoi(line);
			trav = trav->right;
			while (*line && *line != ' ')
				++line;
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

t_node	*create_node_structure(char **lines, int lines_rows)
{	
	t_node	*beg;
	t_node	*trav;
	int		i = 0;
	
	beg = create_list(lines[i]);
	trav = beg;
	i++;
	while (i < lines_rows)
	{
		trav->down = create_list(lines[i]);
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
	printf("%d\n", struct_cols);
	return (struct_cols);
}

int		*pixel_metrics_calculator(int lines_rows, int struct_cols)
{
	int		*pixels;
	int		wide;
	int		heigh;
	int		adjacent;
	int		opposite;

	pixels = (int *)malloc(sizeof(int) * 4);
	wide = 1080;
	heigh = 720;
	if (lines_rows > struct_cols)
		opposite = (wide / 2 - 1)  / (lines_rows - 1);
	else
		opposite = (wide / 2 - 1) / (struct_cols - 1);
	adjacent = opposite / 1.73;
	pixels[0] = wide;
   	pixels[1] = heigh;
	pixels[2] = adjacent;
	pixels[3] = opposite;
	return (pixels);
}

void	assign_coordenates(t_node *trav, int x, int y, int adj, int opp)
{
	trav->x = x;
	trav->y = y;
	if (trav->right)
	{
		assign_coordenates(trav->right, x + opp, y - adj, adj, opp);
	}
	if (trav->left)
	{
		assign_coordenates(trav->left, x - opp, y - adj, adj, opp);
	}
}

void	draw_grid(void *mlx_ptr, void * win_ptr, t_node *trav, int color)
{
	if (trav->right)
	{
		draw_line(mlx_ptr, win_ptr, trav->x, trav->y, trav->right->x, trav->right->y, color);
		draw_grid(mlx_ptr, win_ptr, trav->right, color);
	}
	if (trav->left)
	{
		draw_line(mlx_ptr, win_ptr, trav->x, trav->y, trav->left->x, trav->left->y, color);
		draw_grid(mlx_ptr, win_ptr, trav->left, color);
	}
}

int		main(void)
{
	t_node	*beg;
//	char	*lines[] = { "0 0 0 0 0 0", "0 0 0 0 0 0", "0 0 0 0 0 0", "0 0 0 0 0 0" };
//	char	*lines[] = { "0 0 0 0 0 0 0 0 0 0 0 0", "0 0 0 0 0 0 0 0 0 0 0 0" };
	char	*lines[] = { "-10 2 3", "4 5 6", "7 8 -20" };
	int		lines_rows = 3;
	int		struct_cols;
	int		*pixels;
	void	*mlx_ptr;
	void	*win_ptr;
	
	beg = create_node_structure(lines, lines_rows);
	struct_cols = struct_cols_counter(beg);
	pixels = pixel_metrics_calculator(lines_rows, struct_cols);
	assign_coordenates(beg, pixels[0] / 2, pixels[1] - 1, pixels[2], pixels[3]);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, pixels[0], pixels[1], "fils de fer");
	draw_grid(mlx_ptr, win_ptr, beg, 0xFFFFFF);
	mlx_loop(mlx_ptr);
}

void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1; 
	err = (dx > dy ? dx : - dy) / 2;
	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
		if (x0 == x1 && y0 == y1) 
			break ;
		e2 = err;
		if (e2 >-dx)
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
