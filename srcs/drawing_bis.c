/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:44:49 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/04 23:53:41 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//retourne la valeur absolue de n
int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

//retourne -1 si n est negatif ou 1 si n est positif
int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

//permet d'avoir la distance la plus grande entre celle sur 
//l'axe x et celle sur l'axe y
void	get_distance(t_drawing *draw)
{
	if (absolute(draw->x1 - draw->x0) > absolute(draw->y1 - draw->y0))
	{
		draw->dist = absolute(draw->x1 - draw->x0);
		draw->is_x = 1;
		draw->pos_start = draw->x0;
	}
	else
	{
		draw->dist = -absolute(draw->y1 - draw->y0);
		draw->is_x = 0;
		draw->pos_start = draw->y0;
	}
}

//suite de drawing bis
//(sert a print toute la map sauf la derniere ligne qui est print dans drawing/
//et la derniere colonne qui est dans drawing_bis)
int	drawing_ter(t_data *data, int x, int y)
{	
	while (y < data->height - 1)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y]);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, data->tab[x][y]);
		y++;
	}
	return (y);
}

//suite de la fonction drawing 
//(sert a print la derniere colonne de la map)
int	drawing_bis(t_data *data, int x, int y)
{
	while (x < data->width - 1)
	{
		y = drawing_ter(data, x, y);
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y]);
		y = 0;
		x++;
	}
	return (x);
}
