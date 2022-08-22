/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/22 03:36:43 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_elements_positions(void *data)
{
	int		i;
	int		j;
	t_data	*mlx;

	mlx = (t_data *)data;
	j = 0;
	mlx_clear_window(mlx->ptr, mlx->win);
	while (j < mlx->j)
	{
		i = 0;
		while (i < mlx->i)
		{
			mlx_put_image_to_window(mlx->ptr, mlx->win,
				mlx->img_f, i * 64, j * 64);
			load_image(mlx, &i, &j);
			i++;
		}
		j++;
	}
	return (0);
}

int	quit(void)
{
	exit(0);
	return (0);
}

int	key_hook(int key, void *data)
{
	t_data	*mlx;

	mlx = (t_data *)data;
	if (key == 2 || key == 124)
		move_right(mlx);
	else if (key == 1 || key == 125)
		move_down(mlx);
	else if (key == 0 || key == 123)
		move_left(mlx);
	else if (key == 13 || key == 126)
		move_up(mlx);
	else if (key == 53)
	{
		free_double_pointer(mlx->map);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	mlx;

	if (ac == 2)
	{
		mlx.move = 0;
		mlx.map = map_valid_dimension(av[1], &mlx);
		mlx.collect = collect_search(&mlx, 'C');
		if (mlx.collect < 1)
			ft_exit("ERROR : Not Enough Trophies !");
		if ((collect_search(&mlx, 'P') != 1)
			|| (collect_search(&mlx, 'E') != 1))
			ft_exit("ERROR : You need 1 Player and 1 exit !");
		mlx.ptr = mlx_init();
		ft_mlx(&mlx);
		mlx_key_hook(mlx.win, key_hook, (void *)&mlx);
		mlx_hook(mlx.win, 17, 0, quit, NULL);
		mlx_loop_hook(mlx.ptr, put_elements_positions, (void *)&mlx);
		mlx_loop(mlx.ptr);
	}
	else
		ft_exit("Not the right number of parameters !");
	return (0);
}
