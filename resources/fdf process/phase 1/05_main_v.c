/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/21 17:27:51 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

typedef struct	s_node
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

void	draw_grid(void *mlx_ptr, void * win_ptr, t_node *one)
{
	draw_line(mlx_ptr, win_ptr, one->x, one->y, one->left->x, one->left->y, one->color);
	draw_line(mlx_ptr, win_ptr, one->x, one->y, one->right->x, one->right->y, one->color);
}

t_node	*create_node(int x, int y, int z, int color)
{
	t_node	*beg;

	if (!(beg = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	beg->x = x;
	beg->y = y;
	beg->z = z;
	beg->color = color;
	beg->left = NULL;
	beg->right = NULL;
	return (beg);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		heigh;
	int		wide;
	t_node	*one;
	t_node	*two;
	t_node	*three;

	heigh = 500;
	wide = 600;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test lines");
	
	one = create_node(250, 500, 0, 0xFFFFFF);
	two = create_node(165, 450, 0, 0xFFFFFF);
	three = create_node(335, 450, 0, 0xFFFFFF);
	one->left = two;
	one->right = three;
	draw_grid(mlx_ptr, win_ptr, one);
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
