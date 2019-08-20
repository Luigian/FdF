/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/19 17:29:18 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

int		deal_mouse(int	button, int x, int y, void **param);
int		deal_key(int key, void **param);
void	draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param[2];
	int		heigh;
	int		wide;
	int		x1, y1, x2, y2;

	x1 = 0;
	y1 = 0;
	x2 = 500;
	y2 = 0;
	heigh = 500;
	wide = 500;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test lines");
	while (y1 < 500)
	{
		draw_line(mlx_ptr, win_ptr, x1, y1, x2, y2, 0xFF0000);
		y1 += 20;
	}
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	mlx_mouse_hook(win_ptr, deal_mouse, param);
	mlx_key_hook(win_ptr, deal_key, (void *)0);	
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

int		deal_mouse(int	button, int x, int y, void **param)
{
	if (button == 1)
	{
		draw_line(param[0], param[1], x, y, 250, 250, 0xFFFFFF);
	}
	return (0);
}

int		deal_key(int key, void **param)
{
	if (key == 53)
		exit (0);
	return (0);
}
