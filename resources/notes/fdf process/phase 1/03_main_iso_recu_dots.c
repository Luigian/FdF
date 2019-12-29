/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/21 14:07:41 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

typedef struct	s_node
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

t_node	*create_node(int x, int y, int z, int color, void *mlx_ptr, void *win_ptr)
{
	t_node	*beg;

	if (!(beg = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	beg->x = x;
	beg->y = y;
	beg->z = z;
	beg->color = color;
	mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
	if (x - 86 > 0 && y - 50 > 0)
		beg->left = create_node(x - 86, y - 50, 0, 0xFFFFFF, mlx_ptr, win_ptr);
	if (x + 86 < 600 && y - 50 > 0)
		beg->right = create_node(x + 86, y - 50, 0, 0xFFFFFF, mlx_ptr, win_ptr);
	return (beg);
}

void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

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
	
	one = create_node(250, 500, 0, 0xFFFFFF, mlx_ptr, win_ptr);
	
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
