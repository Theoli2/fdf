/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:59:57 by tlivroze          #+#    #+#             */
/*   Updated: 2023/02/15 16:50:36 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	conv(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (0);
}

int	isinbase(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return (0);
}

int	checksame(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == 43 || str[i] == 45 || str[i] > 126 || str[i] < 32)
			return (1);
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int			n;
	long int	result;

	result = 0;
	n = 1;
	if (ft_strlen(base) <= 1)
		return (0);
	if (checksame(base) == 1)
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str == 45 || *str == 43)
	{
		if (*str == 45)
			n = n * -1;
		str++;
	}
	while (isinbase(*str, base) == 1)
	{
		result = (result * ft_strlen(base)) + conv(*str, base);
		str++;
	}
	result = result * n;
	return (result);
}
