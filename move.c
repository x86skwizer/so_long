/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 00:31:24 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/20 00:51:53 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	exit_game(t_data *mlx)
{
	mlx->map[mlx->y_p / 64][mlx->x_p / 64] = '0';
	ft_printf("GAME OVER\n");
	exit (0);
}

void	move_right(t_data *mlx)
{
	if (mlx->map[mlx->y_p / 64][(mlx->x_p / 64) + 1] == '1')
		return;
	else if (mlx->map[mlx->y_p / 64][(mlx->x_p / 64) + 1] == 'E')
		exit_game(mlx);
	mlx->map[mlx->y_p / 64][mlx->x_p / 64] = '0';
	mlx->map[mlx->y_p / 64][(mlx->x_p / 64) + 1] = 'P';
	mlx->x_p += 64;
	ft_printf("Number of moves : %d\n", ++mlx->move);
}

void	move_down(t_data *mlx)
{
	if (mlx->map[(mlx->y_p / 64) + 1][mlx->x_p / 64] == '1')
		return;
	else if (mlx->map[(mlx->y_p / 64) + 1][mlx->x_p / 64] == 'E')
		exit_game(mlx);
	mlx->map[mlx->y_p / 64][mlx->x_p / 64] = '0';
	mlx->map[(mlx->y_p / 64) + 1][mlx->x_p / 64] = 'P';
	mlx->y_p += 64;
	ft_printf("Number of moves : %d\n", ++mlx->move);
}

void	move_left(t_data *mlx)
{
	if (mlx->map[mlx->y_p / 64][(mlx->x_p / 64) - 1] == '1')
		return;
	else if (mlx->map[mlx->y_p / 64][(mlx->x_p / 64) - 1] == 'E')
		exit_game(mlx);
	mlx->map[mlx->y_p / 64][mlx->x_p / 64] = '0';
	mlx->map[mlx->y_p / 64][(mlx->x_p / 64) - 1] = 'P';
	mlx->x_p -= 64;
	ft_printf("Number of moves : %d\n", ++mlx->move);
}

void	move_up(t_data *mlx)
{
	if (mlx->map[(mlx->y_p / 64) - 1][mlx->x_p / 64] == '1')
		return;
	else if (mlx->map[(mlx->y_p / 64) - 1][mlx->x_p / 64] == 'E')
		exit_game(mlx);
	mlx->map[mlx->y_p / 64][mlx->x_p / 64] = '0';
	mlx->map[(mlx->y_p / 64) - 1][mlx->x_p / 64] = 'P';
	mlx->y_p -= 64;
	ft_printf("Number of moves : %d\n", ++mlx->move);
}