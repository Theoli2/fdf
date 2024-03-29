/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:23:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/22 08:54:48 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//alloue le tableau de vertex en fonction du nombre de colonnes et de lignes
bool	init_tab(t_data data, t_vertex ***tab)
{
	int	k;

	(*tab) = ft_calloc(data.width + 1, sizeof(t_vertex *));
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

//s'occupe de remplir chaque ligne du tableau avec les coordonnes des points
// et eventuellement la couleur si elle est presente dans le fichier
void	sub_fill_tab(t_data	*data, t_vertex	**tab, t_parse parse, char **points)
{
	int	i;

	while (parse.k < data->height)
	{
		tab[parse.l][parse.k].x = parse.l;
		tab[parse.l][parse.k].y = parse.k;
		tab[parse.l][parse.k].z = ft_atoi(points[parse.k]);
		if (ft_strchr(points[parse.k], ',') != NULL)
		{
			i = 0;
			while (points[parse.k][i++])
				points[parse.k][i] = ft_toupper(points[parse.k][i]);
			tab[parse.l][parse.k].file_color
				= ft_atoi_base(ft_strchr(points[parse.k], 'X') + 1, HEXA);
		}
		else
			tab[parse.l][parse.k].file_color = 0xFFFFFF;
		free(points[parse.k]);
		parse.k++;
	}
	return (free(points[parse.k]), free(points));
}

//s'occupe de mettre les donnees du fichier dans le tableau
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

//fonction qui permet de parser la map et de la mettre dans un tableau de vertex
//compte le nombre de lignes et de colonnes
bool	parsing(char *file, t_data *data, t_vertex ***tab)
{
	int		fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
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
	if (init_tab(*data, tab) == false)
	{
		error_management(data);
		return (false);
	}
	fill_tab(file, data, *tab);
	return (true);
}
