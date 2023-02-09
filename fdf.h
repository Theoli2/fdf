/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:24:06 by tlivroze          #+#    #+#             */
/*   Updated: 2023/02/09 09:31:02 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define LENGTH 1280
# define WIDTH 720
// # include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vertex {
	int		x;
	int		y;
	int		z;
	int		color;
}				t_vertex;

void		parsing(char *file, t_vertex ***tab);
void		check_matrix(t_vertex **tab, int x, int y);
#endif
