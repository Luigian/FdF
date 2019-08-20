/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/10 22:17:26 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		ft_putchar(*s++);
	}
}

int		deal_key(int key, void *param)
{
	ft_putstr("hola\n");
	return (0);
}

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
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
}
