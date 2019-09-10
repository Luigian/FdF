/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 10:20:31 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/01 11:59:11 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

char	**gen_map_from_file(char **av)
{
	int		fd;
	char	**lines;
	char	**beg;
	int		ret;

	lines = (char **)malloc(sizeof(char *) * 100); 
	beg = lines;
	fd = open(av[1], O_RDONLY, 0);
	while ((ret = get_next_line(fd, lines)) > 0)
		++lines;
	*lines = NULL;
	lines = beg;
	while (*lines)
	{
		printf("%s\n", *lines);
		++lines;
	}
	return (beg);
}

int		main(int ac, char **av)
{
	char	**lines;

	if (ac != 2)
	{
		write(1, "Usage : ./fdf <filename>\n", 25);
		exit(0);
	}
	lines = gen_map_from_file(av);
	return (0);
}
