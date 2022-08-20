/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 03:58:11 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/20 04:40:30 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_mlx(t_data *mlx)
{
	mlx->win = mlx_new_window(mlx->ptr, mlx->i * 64, mlx->j * 64, "so_long");
	mlx->img_f = mlx_xpm_file_to_image(mlx->ptr, "./images/floor.xpm",
			&mlx->img_width, &mlx->img_height);
	mlx->img_w = mlx_xpm_file_to_image(mlx->ptr, "./images/wall.xpm",
			&mlx->img_width, &mlx->img_height);
	mlx->img_p = mlx_xpm_file_to_image(mlx->ptr, "./images/ralph.xpm",
			&mlx->img_width, &mlx->img_height);
	mlx->img_c = mlx_xpm_file_to_image(mlx->ptr, "./images/trophy.xpm",
			&mlx->img_width, &mlx->img_height);
	mlx->img_e = mlx_xpm_file_to_image(mlx->ptr, "./images/door.xpm",
			&mlx->img_width, &mlx->img_height);
}

void	load_image(t_data *mlx, int *i, int *j)
{
	if (mlx->map[(*j)][(*i)] == '1')
		mlx_put_image_to_window(mlx->ptr, mlx->win,
			mlx->img_w, (*i) * 64, (*j) * 64);
	else if (mlx->map[(*j)][(*i)] == '0')
		mlx_put_image_to_window(mlx->ptr, mlx->win,
			mlx->img_f, (*i) * 64, (*j) * 64);
	else if (mlx->map[(*j)][(*i)] == 'P')
	{
		mlx->x_p = (*i) * 64;
		mlx->y_p = (*j) * 64;
		mlx_put_image_to_window(mlx->ptr, mlx->win,
			mlx->img_p, mlx->x_p, mlx->y_p);
	}
	else if (mlx->map[(*j)][(*i)] == 'C')
		mlx_put_image_to_window(mlx->ptr, mlx->win,
			mlx->img_c, (*i) * 64, (*j) * 64);
	else if (mlx->map[(*j)][(*i)] == 'E')
		mlx_put_image_to_window(mlx->ptr, mlx->win,
			mlx->img_e, (*i) * 64, (*j) * 64);
}

int	read_player_exit(char *line, int i, int *player, int *exitvar)
{
	if (line[i] == 'P')
	{
		if (*player == 0)
			*player += 1;
		else
			return (-1);
	}
	else if (line[i] == 'E')
	{
		if (*exitvar == 0)
			*exitvar += 1;
		else
			return (-1);
	}
	return (0);
}
