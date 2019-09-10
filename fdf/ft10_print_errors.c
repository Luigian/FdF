/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:47:14 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 09:38:45 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error_and_exit(int code)
{
	if (code == 1)
	{
		write(1, "Usage : ./fdf <filename>\n", 25);
		exit(code);
	}
	else if (code == 2)
	{
		write(1, "Invalid file. Exiting\n", 22);
		exit(code);
	}
	else if (code == 3)
	{
		write(1, "Found wrong line length. Exiting.\n", 34);
		exit(code);
	}
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	increase_decrease_y_coordenate(void **param, int dir)
{
	t_node		*trav;
	t_node		*beg;

	trav = (t_node *)(param[2]);
	while (trav)
	{
		beg = trav;
		while (trav)
		{
			trav->isoy = trav->isoy - (trav->z * (dir ? Z_SPEED : (-Z_SPEED)));
			trav = trav->left;
		}
		trav = beg->down;
	}
}
