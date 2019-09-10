/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 02:13:13 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 05:37:26 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_line(int fd, int *count, char *line)
{
	close(fd);
	free(count);
	free(line);
}

t_node	*create_structure_of_nodes(int fd, t_map *map)
{
	int		*count;
	int		ret;
	char	*line;
	t_node	*prev;
	t_node	*trav;

	count = (int *)malloc(sizeof(int) * 1);
	*count = 0;
	prev = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(trav = create_list(line, count, map)))
		{
			close(fd);
			free(count);
			return (NULL);
		}
		if (prev)
			connect_up(prev, trav);
		prev = trav;
		trav = trav->down;
	}
	free_line(fd, count, line);
	return (prev);
}

int		read_file(char **av)
{
	int		fd;

	if ((fd = open(av[1], O_RDONLY, 0)) == -1)
		print_error_and_exit(2);
	return (fd);
}

t_map	*initialize_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map) * 1);
	map->rows = 0;
	map->cols = 0;
	map->adj = 0;
	map->opp = 0;
	map->z = 0;
	map->x = 0;
	map->y = 0;
	map->on = 1;
	map->xs = 0;
	map->ys = 0;
	map->zoom = 0;
	map->proj = 1;
	map->win_heigh = 720;
	map->win_wide = 1080;
	map->max_z = 0;
	map->min_z = 0;
	map->color = 0;
	return (map);
}

int		main(int ac, char **av)
{
	t_map		*map;
	t_node		*beg;

	if (ac == 2)
	{
		map = initialize_map();
		if (!(beg = create_structure_of_nodes(read_file(av), map)))
		{
			free(map);
			print_error_and_exit(3);
		}
		get_rows_and_cols(beg, map);
		get_adjacent_and_opposite(map);
		get_x_y_start(map);
		assign_coordenates(beg, map);
		beg = move_pointer_to_top_right_corner(beg);
		open_graphic_interface(beg, map);
	}
	else
		print_error_and_exit(1);
	return (0);
}
