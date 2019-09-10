/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/21 22:29:42 by lusanche         ###   ########.fr       */
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

	if (*line == '0')
		beg = create_node();
	trav = beg;
	++line;
	while (*line)
	{
		if (*line == '0')
		{
			trav->right = create_node();
			trav = trav->right;			
		}
		++line;
	}
	trav->right = NULL;
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

void	assign_coordenates(t_node *trav, int x, int y)
{
	printf("hola");
	trav->x = x;
	trav->y = y;
	if (trav->right)
		assign_coordenates(trav->right, x + 50, y);
	if (trav->left)
		assign_coordenates(trav->left, x, y - 50);
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
	void	*mlx_ptr;
	void	*win_ptr;
	int		heigh;
	int		wide;
	t_node	*beg;
	t_node	*trav;
	char	*lines[] = { "0 0 0 0 0 0", "0 0 0 0 0 0", "0 0 0 0 0 0",\
						"0 0 0 0 0 0" };
	int		size = 4;
	int		i = 0;

	heigh = 500;
	wide = 600;
	beg = create_list(lines[i]);
	trav = beg;
	i++;
	while (i < size)
	{
		trav->down = create_list(lines[i]);
		connect_left(trav, trav->down);
		trav = trav->down;
		++i;
	}
	assign_coordenates(trav, 50, 400);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test lines");
	draw_grid(mlx_ptr, win_ptr, trav, 0xFFFFFF);
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
