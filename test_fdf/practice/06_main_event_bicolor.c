/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/13 23:11:57 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>

int		deal_key(int key, void **param)
{
	int		x;
	int		*y;
	int		lines;
	int		color;

	color = 0xFFFF33;
	if (*(int*)param[2] % 2 == 0)
		color = 0xCCCC00;
	lines = 7;
	y = param[2];
	while (lines--)
	{
		x = 0;
		while (x < 500)
		{
			mlx_pixel_put(param[0], param[1], x, *y, color); 
			++x;
		}
		(*y)++;
	}
//	*(int*)param[2] = *(int*)param[2] + 1;
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param[3];
	int		heigh;
	int		wide;

	heigh = 500;
	wide = 500;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test");
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	*(int*)param[2] = 0;
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_loop(mlx_ptr);
}
