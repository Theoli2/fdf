/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:23:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/17 23:11:14 by tlivroze         ###   ########.fr       */
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

void	init_color(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			data->tab[x][y].color = \
			get_perfect_gradient(data, data->tab[x][y].z);
			y++;
		}
		x++;
	}
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
	lowest_tallest(data);
	init_color(data);
	printf("%i\n", data->draw.lowest);
	return ;
}

/*
(calculer point_gradient pendant le parsing et stocker color dans tab machin.color)
dans put line :
2 vertex;
calcule les distances x et y entre les 2;
trouver la plus grande; 
calculer la distance entre le x ou le y du current pixel et du point de depart;
pour chaque valeur r g et b des color des vertex faire :
color1 - color2;
faire produit en croix pour chaque valeur rgb pour mapper la distance entre
le current pixel et le point de depart sur la distance entre les 2 vertex;
envoyer la couleur recombinee a my_pixel_put;

00000000 00010011 11001010 00011010

00000000 00000000 00000000 11111111 B

00000000 00000000 11111111 00000000 V

00000000 11111111 00000000 00000000 R

00000000 00000000 00000000 00011010
*/
