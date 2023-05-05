/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 00:26:14 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 01:57:50 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

int	drawing_reverse_ter(t_data *data, int x, int y)
{	
	while (y > 0)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x - 1][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x - 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x - 1][y]);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y - 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y - 1], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x][y - 1]);
		y--;
	}
	return (y);
}

int	drawing_reverse_bis(t_data *data, int x, int y)
{
	while (x > 0)
	{
		y = drawing_reverse_ter(data, x, y);
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x - 1][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x - 1][y], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x - 1][y]);
		y = data->height - 1;
		x--;
	}
	return (x);
}

//fait la meme chose que drawing_bis mais a l'envers
//(pour afficher la map lorsqu'une rotation est faite)
int	drawing_reverse(t_data *data)
{
	int			x;
	int			y;

	x = data->width - 1;
	y = data->height - 1;
	x = drawing_reverse_bis(data, x, y);
	while (y > 0)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y - 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y - 1], *data);
		putline(data->draw, data->img, data->tab[x][y], data->tab[x][y - 1]);
		y--;
	}
	return (0);
}
