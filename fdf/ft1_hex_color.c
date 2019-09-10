/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:11:39 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 03:56:22 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_hex(const char *str)
{
	int		num;
	long	result;

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = *str - 48;
		else if (*str >= 'a' && *str <= 'f')
			num = (*str - 'a') + 10;
		else if (*str >= 'A' && *str <= 'F')
			num = (*str - 'A') + 10;
		else
			break ;
		result = (result * 16) + num;
		++str;
	}
	return ((int)result);
}

int		ft_strlen_hex(char *str)
{
	int i;

	i = 0;
	while (str[i] && (ft_isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'f')\
		|| (str[i] >= 'A' && str[i] <= 'F')))
		++i;
	return (i);
}

void	copy_hex_in_channels_biarray(char *hex, char **channels)
{
	int		len;
	int		last;
	int		i;
	int		j;

	hex += 2;
	len = ft_strlen_hex(hex);
	last = len - 1;
	i = 2;
	j = 1;
	while (len--)
	{
		channels[i][j] = hex[last--];
		if (j)
			--j;
		else
		{
			if (!i)
				break ;
			--i;
			j = 1;
		}
	}
}

void	initialize_channels_with_ceros(char **channels)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		channels[i] = ft_strnew(2);
		j = 0;
		while (j < 2)
			channels[i][j++] = '0';
		++i;
	}
}

void	assign_color_to_node(char *hex, t_node *beg)
{
	char	**channels;

	channels = ft_stranew(3);
	initialize_channels_with_ceros(channels);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		copy_hex_in_channels_biarray(hex, channels);
	beg->color.red = ft_atoi_hex(channels[0]);
	beg->color.green = ft_atoi_hex(channels[1]);
	beg->color.blue = ft_atoi_hex(channels[2]);
	free_array(channels);
}
