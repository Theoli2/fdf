/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 02:53:13 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/03 02:54:21 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	error_management(t_data	*data)
{
	int	k;

	k = 0;
	while (k < data->width)
	{
		free(data->tab[k]);
		k++;
	}
	free(data->tab);
}
