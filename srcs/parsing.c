/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:23:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/13 14:21:56 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

bool	init_tab(t_data data, t_vertex ***tab)
{
	int	k;

	(*tab) = malloc(sizeof(t_vertex *) * (data.width + 1));
	if (*tab == NULL)
		return (false);
	k = 0;
	while (k < data.width)
	{
		(*tab)[k] = malloc(sizeof(t_vertex) * data.height);
		if ((*tab)[k] == NULL)
			return (false);
		k++;
	}
	(*tab)[k] = NULL;
	return (true);
}

void	sub_fill_tab(t_data	*data, t_vertex	**tab, t_parse parse, char **points)
{
	int	i;

	while (parse.k < data->height)
	{
		tab[parse.l][parse.k].x = parse.l;
		tab[parse.l][parse.k].y = parse.k;
		tab[parse.l][parse.k].z = ft_atoi(points[parse.k]);
		data->draw.lowest = lowest(tab[parse.l][parse.k].z, *data);
		data->draw.tallest = tallest(tab[parse.l][parse.k].z, *data);
		if (ft_strchr(points[parse.k], ',') != NULL)
		{
			i = 0;
			while (points[parse.k][i++])
				points[parse.k][i] = ft_toupper(points[parse.k][i]);
			tab[parse.l][parse.k].color
				= ft_atoi_base(ft_strchr(points[parse.k], 'X') + 1, HEXA);
		}
		else
			tab[parse.l][parse.k].color = -1;
		free(points[parse.k]);
		parse.k++;
	}
	return (free(points[parse.k]), free(points));
}

bool	fill_tab(char *file, t_data *data, t_vertex **tab)
{
	char	*s;
	char	**points;
	t_parse	parse;
	char	fd;

	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	parse.l = 0;
	while (s)
	{
		parse.k = 0;
		points = ft_split(s, ' ');
		sub_fill_tab(data, tab, parse, points);
		free(s);
		s = get_next_line(fd);
		parse.l++;
	}
	close(fd);
	return (true);
}

void	parsing(char *file, t_data *data, t_vertex ***tab)
{
	int		fd;
	char	*s;

	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	data->width = 0;
	s = ft_strtrim(s, " \n");
	data->height = countwords(s, ' ');
	while (s)
	{
		free(s);
		s = get_next_line(fd);
		data->width++;
	}
	free(s);
	close(fd);
	init_tab(*data, tab);
	fill_tab(file, data, *tab);
	return ;
}
