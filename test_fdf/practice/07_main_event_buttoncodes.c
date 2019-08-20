/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 16:44:44 by lusanche          #+#    #+#             */
/*   Updated: 2019/08/15 09:07:24 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>

void	ft_putnbr(int n)
{
	char	c;
	if (n >= 10)
		ft_putnbr(n / 10);
	n = n % 10;
	c = n + 48;
	write(1, &c, 1);
}

int		deal_mouse(int button,int x, int y, void **param)
{
	ft_putnbr(button);
	write(1, " [", 2);
	ft_putnbr(x);
	write(1, "] [", 3);
	ft_putnbr(y);
	write(1, "]\n", 2);
	return (0);
}

int		deal_key(int key, void **param)
{
	ft_putnbr(key);
	write(1, "\n", 1);
	printf("%d", key);
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*param[2];
	int		heigh;
	int		wide;

	heigh = 500;
	wide = 500;
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wide, heigh, "mlx test");
	param[0] = mlx_ptr;
	param[1] = win_ptr;
	mlx_key_hook(win_ptr, deal_key, param);
	mlx_mouse_hook(win_ptr, deal_mouse, param);
	mlx_loop(mlx_ptr);
}
