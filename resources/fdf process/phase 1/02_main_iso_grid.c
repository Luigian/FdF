/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/20 20:56:08 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		heigh;
	int		wide;
	int		x1, y1, x2, y2;

	heigh = 500;
	wide = 600;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test lines");
	draw_line(mlx_ptr, win_ptr, 250, 500, 80, 400, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 250, 500, 505, 350, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 335, 250, 80, 400, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 335, 250, 505, 350, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 335, 450, 165, 350, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 420, 400, 250, 300, 0xFF0000);
	draw_line(mlx_ptr, win_ptr, 165, 450, 420, 300, 0xFF0000);
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
