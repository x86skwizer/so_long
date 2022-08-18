/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/18 18:49:59 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
int check_line(char *line, int len, int *player)
{

	int i;
	
	i = 0;
	if (line[0] != '1' || line[len - 1] != '1')
		return (-1);
	while (line[i] && i < len)
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C' && line[i] != 'E' && line[i] != 'P')
			return (-1);
		if (line[i] == 'P')
		{
			if (*player == 0)
				*player += 1;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

int check_wall(char *line)
{
	int index;
	
	index = 0;
	while (line[index])
	{
		if (line[index] != '1')
			return (-1);
		index++;
	}
	return (0);
}

int check_map_file(char *av)
{
	char *ext;
	int status;
	int fd;

	ext = ft_substr(av, ft_strlen(av) - 4, 4);
	status = ft_strncmp(ext, ".ber", ft_strlen(ext));
	fd = open(av, O_RDONLY);
	if (status != 0 || fd == -1)
	{
		ft_printf("ERROR : Map name incorrect !\n");
		exit(-1);
	}
	return (fd);
}

void ft_exit(char *message)
{
	ft_printf("%s\n", message);
	exit(-1);
}

int count_line(char *s)
{
	int index;

	index = 0;
	while (s[index])
		index++;
	if (s[index - 1] == '\n')
		index--;
	return (index);
}

void save_line(char **dist, char *line)
{
	char *tmp;

	tmp = ft_strjoin(*dist, line);
	free(*dist);
	*dist = tmp;
}

void	initialize_map(t_space *env, char *av)
{
	env->counter = 0;
	env->p_status = 0;
	env->len = 0;
	env->saved_lines = ft_strdup("");
	env->fd = check_map_file(av);
}

char **map_valid_dimension(char *av, t_counter *dimension)
{
	t_space	env;

	initialize_map(&env, av);
	while (1)
	{
		env.line = get_next_line(env.fd);
		if (!env.line)
			break;
		if (env.len == 0)
			env.len = count_line(env.line);
		else if (env.len != count_line(env.line))
			ft_exit("ERROR : Invalid line !");
		env.ret = check_line(env.line, env.len, &env.p_status);
		if (env.ret == -1)
			ft_exit("ERROR : Invalid map structure !");
		save_line(&env.saved_lines, env.line);
		free(env.line);
		env.line = NULL;
		env.counter++;
	}
	env.map = ft_split(env.saved_lines, '\n');
	if (check_wall(env.map[0]) || check_wall(env.map[env.counter - 1]))
		ft_exit("ERROR : Invalid wall structure !");
	dimension->i = env.len;
	dimension->j = env.counter;
	return (env.map);
}

void	put_elements_positions(t_data mlx, t_counter	dimension, char **map)
{
	int i;
	int j;

	j = 0;
	while (j < dimension.j)
		{
			i = 0;
			while (i < dimension.i)
			{
				mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./floor.xpm", &mlx.img_width, &mlx.img_height);
				mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64, j * 64);
				if (map[j][i] == '1')
				{
					mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./wall.xpm", &mlx.img_width, &mlx.img_height);
					mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64, j * 64);
				}
				else if (map[j][i] == '0')
				{
					mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./floor.xpm", &mlx.img_width, &mlx.img_height);
					mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64, j * 64);
				}
				else if (map[j][i] == 'P')
				{
					mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./ralph.xpm", &mlx.img_width, &mlx.img_height);
					mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64 , j * 64);
				}
				else if (map[j][i] == 'C')
				{
					mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./trophy.xpm", &mlx.img_width, &mlx.img_height);
					mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64, j * 64);
				}
				else if (map[j][i] == 'E')
				{
					mlx.img = mlx_xpm_file_to_image(mlx.ptr, "./door.xpm", &mlx.img_width, &mlx.img_height);
					mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, i * 64, j * 64);
				}
				i++;
			}
			j++;
		}
}

int key_hook(int key, t_data *mlx)
{
	ft_printf("key : %d\n", key);
	mlx->x += 64;
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./ralph.xpm", &mlx->img_width, &mlx->img_height);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, mlx->x, mlx->y);
	return 0;
}

int main(int ac, char **av)
{
	t_data	mlx;
	char	**map;
	t_counter	dimension;

	if (ac == 2)
	{
		map = map_valid_dimension(av[1], &dimension);
		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, dimension.i * 64, dimension.j * 64, "so_long");
		put_elements_positions(mlx, dimension, map);
		//mlx_key_hook(mlx.win, key_hook, &mlx);
		mlx_loop(mlx.ptr);
	}
	else
		ft_exit("Not the right number of parameters !");
	return 0;
}