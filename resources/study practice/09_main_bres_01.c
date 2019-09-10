/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/19 17:16:21 by lusanche         ###   ########.fr       */
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
	wide = 500;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test lines");
	draw_line(mlx_ptr, win_ptr, 10, 10, 400, 400, 0xFF0000);
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

/*
void	draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : - dy) / 2, e2;
	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
//		setPixel(x0,y0);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}
*/
/*
void		draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, p, x, y;
	
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;
	p = 2 * dy - dx;
	while (x < x1)
	{
		if (p >= 0)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
//			putpixel(x, y, 7);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
//			putpixel(x, y, 7);
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			p = p + 2 * dy;
		}
		x = x + 1;
	}	
}
*/
/*
int		draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
	int		x, y, dx, dy, p, end, slope, sx, sy, ab_dy, ab_dx;
	
	if (x1 == x2 && y1 == y2)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
		return (0);
	}
	dx = (x2 - x1);
	sx = dx < 0 ? -1 : 1;
	dy = (y2 - y1);
	sy = dy < 0 ? -1 : 1;

	ab_dx = dx * (dx < 0 ? -1 : 1); 
	ab_dy = dy * (dy < 0 ? -1 : 1); 
	if (abs(dy) < abs(dx))
	{
		slope = dy / dx;
		p = y1 - slope * x1;
		while (x1 != x2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x1, round(slope * x1 + p), color);
			x1 += sx;
		}
	}
	else
	{
		slope = dx / dy;
		p = x1 - slope * y1;
		while (y1 != y2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, round(slope * y1 + p), y1, color);
			y1 += sy;
		}
	}
	mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, color);
	return (0);
}
*/
