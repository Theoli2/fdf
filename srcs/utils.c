/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 02:53:13 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/04 22:12:54 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

//est appelle si jamais un malloc a fail et free le tableau
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
