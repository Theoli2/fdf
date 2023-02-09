/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:23:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/02/09 16:28:34 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

bool	init_tab(t_vertex ***tab, int height, int width)
{
	int	k;
	printf("h = %i, w  = %i\n",height,width);
	(*tab) = malloc(sizeof(t_vertex *) * height);
	printf("ping\n");
	if (*tab == NULL)
		return (false);
	k = 0;
	while (k < height)
	{
		(*tab)[k] = malloc(sizeof(t_vertex) * width);
		if ((*tab)[k] == NULL)
			return (printf("test\n"));
		k++;
	}
	printf("ping\n");
	return (printf("test2\n"));
}

bool	fill_tab(char *file, t_vertex **tab, int width)
{
	char	*s;
	char	**points;
	int		k;
	int		l;
	char	fd;

	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	l = 0;
	while (s)
	{
		k = 0;
		points = ft_split(s, ' ');
		while (k <= width)
		{
			printf("ping\n");
			tab[l][k].x = l;
			tab[l][k].y = k;
			tab[l][k].z = ft_atoi(points[k]);
			free(points[k]);
			k++;
		}
		free(points);
		free(s);
		s = get_next_line(fd);
		l++;
	}
	k = 0;
	close(fd);
	return (true);
}

void	parsing(char *file, t_vertex ***tab)
{
	int		fd;
	int		height;
	int		width;
	char	*s;

	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	height = 0;
	s = ft_strtrim(s, " \n");
	width = countwords(s, ' ');
	printf("%i", width);
	while (s)
	{
		free(s);
		s = get_next_line(fd);
		height++;
	}
	free(s);
	close(fd);
	init_tab(tab, height, width);
	fill_tab(file, *tab, width);
	check_matrix(*tab, height, width);
	return ;
}
