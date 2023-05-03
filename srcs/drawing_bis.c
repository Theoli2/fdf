/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:44:49 by tlivroze          #+#    #+#             */
/*   Updated: 2023/04/26 23:24:00 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

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
