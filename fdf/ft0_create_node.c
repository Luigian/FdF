/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:11:30 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 03:44:53 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	prepare_next_node(t_node *trav, char *data, t_map *map)
{
	trav->right = create_node();
	assign_data_to_node(trav->right, data, map);
	trav->right->left = trav;
}

void	assign_data_to_node(t_node *trav, char *data, t_map *map)
{
	char	**z_hex;

	z_hex = ft_strsplit(data, ',');
	trav->z = ft_atoi(z_hex[0]);
	trav->z > map->max_z ? map->max_z = trav->z : 0;
	trav->z < map->min_z ? map->min_z = trav->z : 0;
	if (z_hex[1])
	{
		assign_color_to_node(z_hex[1], trav);
	}
	free_array(z_hex);
}

t_node	*create_node(void)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node) * 1)))
		return (NULL);
	node->isox = 0;
	node->isoy = 0;
	node->plax = 0;
	node->play = 0;
	node->frox = 0;
	node->froy = 0;
	node->z = 0;
	node->color.red = 255;
	node->color.green = 255;
	node->color.blue = 255;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	return (node);
}

int		validate_data_packets_count(char **data, int *count)
{
	int		i;

	i = 0;
	while (data[i])
		++i;
	if (*count)
	{
		if (*count != i)
		{
			free_array(data);
			return (0);
		}
	}
	else
		*count = i;
	return (1);
}

t_node	*create_list(char *line, int *count, t_map *map)
{
	t_node	*beg;
	t_node	*trav;
	char	**data;
	char	**data_beg;

	if (!(validate_data_packets_count(data = ft_strsplit(line, ' '), count)))
		return (NULL);
	beg = NULL;
	data_beg = data;
	if (*data)
	{
		beg = create_node();
		assign_data_to_node(beg, *data, map);
		++data;
		trav = beg;
		while (*data)
		{
			prepare_next_node(trav, *data, map);
			trav = trav->right;
			++data;
		}
	}
	free_array(data_beg);
	return (beg);
}
