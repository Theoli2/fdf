/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:44:49 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/14 20:08:19 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	drawing_ter(t_data *data, int x, int y)
{	
	while (y < data->height - 1)
	{
		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, get_perfect_gradient(data, data->tab[x][y].z));
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x][y + 1], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x][y + 1], *data);
		putline(data->draw, data->img, get_perfect_gradient(data, data->tab[x][y].z));
		y++;
	}
	return (y);
}

int	drawing_bis(t_data *data, int x, int y)
{
	while (x < data->width - 1)
	{
		y = drawing_ter(data, x ,y);

		data->draw.x0 = calculate_x(data->offset_x, data->tab[x][y], *data);
		data->draw.y0 = calculate_y(data->offset_y, data->tab[x][y], *data);
		data->draw.x1 = calculate_x(data->offset_x, data->tab[x + 1][y], *data);
		data->draw.y1 = calculate_y(data->offset_y, data->tab[x + 1][y], *data);
		putline(data->draw, data->img, get_perfect_gradient(data, data->tab[x][y].z));
		y = 0;
		x++;
	}
	return (x);
}
