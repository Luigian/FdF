/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/10 22:04:58 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	int		heigh;
	int		wide;
	int		x;
	int		y;
	int		color;

	heigh = 500;
	wide = 500;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test");
	color = 0xFFFF33;
	x = 0;
	while (x < wide)
	{
		y = wide / 2;
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color); 
		++x;
	}
	y = 0;
	while (y < heigh)
	{
		x = heigh / 2;
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color); 
		++y;
	}
	
	mlx_loop(mlx_ptr);
}
