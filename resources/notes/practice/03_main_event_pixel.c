/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/11 22:01:26 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>

int		deal_key(int key, void **param)
{
	mlx_pixel_put(param[0], param[1], 200, 200, 0xFFFF33); 
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	void	*param[2];
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
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_loop(mlx_ptr);
}
