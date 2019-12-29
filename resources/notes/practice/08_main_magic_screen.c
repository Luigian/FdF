/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/16 15:19:14 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	print_background(void *mlx_ptr, void *win_ptr, int heigh, int wide);
void	ft_putnbr(int n);

int		deal_mouse(int button,int i, int j, void **param)
{
	int		x;
	int		y;
	int		direction;
	int		n;
	int		m;
	int		color;
	int		color_head;

	x = ((int*)(param[2]))[0];
	y = ((int*)(param[2]))[1];
	direction = ((int*)(param[2]))[2];
	n = 20;
	m = n;
	color = 0x808080;
	color_head = 0xFFFFFF;
	if (x <= 60)
		(((int*)(param[2]))[0]) = 61;
	if (x >= 639)
		(((int*)(param[2]))[0]) = 638;
	if (y <= 60)
		(((int*)(param[2]))[1]) = 61;
	if (y >= 439)
			(((int*)(param[2]))[1]) = 438;
	if (button == 2)
		print_background(param[0], param[1], 500, 700);
	else if (button == 1)
	{
		if (direction == 1)
			((int*)(param[2]))[2] = 2;
		else if (direction == 2)
			((int*)(param[2]))[2] = 1;
	}
	else if (direction == 1)
	{
		if (button == 4)
		{
			while (m--)
			{
				if (x > 60 && x < 639)
				{	
					mlx_pixel_put(param[0], param[1], x++, y, color);
					((int*)(param[2]))[0] = ((int*)(param[2]))[0] + 1;
				}
			}
			if (x > 60 && x < 639)
				mlx_pixel_put(param[0], param[1], x, y, color_head);
		}
		if (button == 5)
		{
			while (m--)
			{
				if (x > 60 && x < 639)
				{
					mlx_pixel_put(param[0], param[1], x--, y, color);
					((int*)(param[2]))[0] = ((int*)(param[2]))[0] - 1;
				}
			}
			if (x > 60 && x < 639)
				mlx_pixel_put(param[0], param[1], x, y, color_head);
		}
	}
	else if (direction == 2)
	{
		if (button == 5)
		{
			while (m--)
			{
				if (y > 60 && y < 439)
				{
					mlx_pixel_put(param[0], param[1], x, y++, color);
					((int*)(param[2]))[1] = ((int*)(param[2]))[1] + 1;
				}
			}
			if (y > 60 && y < 439)
				mlx_pixel_put(param[0], param[1], x, y, color_head);
		}
		if (button == 4)
		{
			while (m--)
			{
				if (y > 60 && y < 439)
				{
					mlx_pixel_put(param[0], param[1], x, y--, color);
					((int*)(param[2]))[1] = ((int*)(param[2]))[1] - 1;
				}
			}
			if (y > 60 && y < 439)
				mlx_pixel_put(param[0], param[1], x, y, color_head);
		}
	}
//	ft_putnbr(button);
	return (0);
}

int		main(void)
{
	void	*param[3];
	void	*mlx_ptr;
	void	*win_ptr;
	int		*coord;
	int		heigh;
	int		wide;

	heigh = 500;
	wide = 700;
	coord = (int *)malloc(sizeof(int) * 3);
	coord[0] = 60;
	coord[1] = 60;
	coord[2] = 1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test");
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	print_background(mlx_ptr, win_ptr, heigh, wide);	
	param[2] = coord;
	mlx_mouse_hook(win_ptr, deal_mouse, param);
	mlx_loop(mlx_ptr);
}

void	print_background(void *mlx_ptr, void *win_ptr, int heigh, int wide)
{
	int		x;
	int		y;
	int		h;
	int		w;
	int		color_background;
	int		color_frame;
	
	color_background = 0xC0C0C0;
	color_frame = 0xB22222;
	y = 0;
	while (y < heigh)
	{
		x = 0;
		while ( x < wide)
			mlx_pixel_put(mlx_ptr, win_ptr, x++, y, color_background);
		y++;
	}
	h = 60;
	y = 0;
	while (y < h)
	{
		x = 0;
		while ( x < wide)
			mlx_pixel_put(mlx_ptr, win_ptr, x++, y, color_frame);
		y++;
	}
	y = heigh - h;
	while (y < heigh)
	{
		x = 0;
		while ( x < wide)
			mlx_pixel_put(mlx_ptr, win_ptr, x++, y, color_frame);
		y++;
	}
	y = 0;
	while (y < heigh)
	{
		x = 0;
		while (x < h)
			mlx_pixel_put(mlx_ptr, win_ptr, x++, y, color_frame);
		y++;
	}
	y = 0;
	while (y < heigh)
	{
		x = wide - h;
		while (x < wide)
			mlx_pixel_put(mlx_ptr, win_ptr, x++, y, color_frame);
		y++;
	}
}

void	ft_putnbr(int n)
{
	char	c;
	if (n >= 10)
		ft_putnbr(n / 10);
	n = n % 10;
	c = n + 48;
	write(1, &c, 1);
}
