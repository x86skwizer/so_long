/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:21:58 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/19 04:09:35 by yamrire          ###   ########.fr       */
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

char **map_valid_dimension(char *av, t_data *mlx)
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
	mlx->i = env.len;
	mlx->j = env.counter;
	return (env.map);
}

int	put_elements_positions(void *data)
{
	int i;
	int j;
	t_data *mlx;
	
	mlx = (t_data *)data;
	j = 0;
	while (j < mlx->j)
		{
			i = 0;
			while (i < mlx->i)
			{
				mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_f, i * 64, j * 64);
				if (mlx->map[j][i] == '1')
					mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_w, i * 64, j * 64);
				else if (mlx->map[j][i] == '0')
					mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_f, i * 64, j * 64);
				else if (mlx->map[j][i] == 'P')
				{
					mlx->x_p = i * 64;
					mlx->y_p = j * 64;
					mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_p, mlx->x_p , mlx->y_p);
				}
				else if (mlx->map[j][i] == 'C')
					mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_c, i * 64, j * 64);
				else if (mlx->map[j][i] == 'E')
					mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_e, i * 64, j * 64);
				i++;
			}
			j++;
		}
		printf("frame\n");
		return (0);
}

// int key_hook(int key, void *data)
// {
// 	t_data *mlx;
	
// 	mlx = (t_data *)data;
// 	ft_printf("key : %d\n", key);
// 	mlx->x += 64;
// 	mlx_clear_window(mlx->ptr, mlx->win);
// 	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./ralph.xpm", &mlx->img_width, &mlx->img_height);
// 	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, mlx->x, mlx->y);
// 	return 0;
// }

int main(int ac, char **av)
{
	t_data	mlx;

	if (ac == 2)
	{
		mlx.map = map_valid_dimension(av[1], &mlx);
		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, mlx.i * 64, mlx.j * 64, "so_long");
		mlx.img_f = mlx_xpm_file_to_image(mlx.ptr, "./floor.xpm", &mlx.img_width, &mlx.img_height);
		mlx.img_w = mlx_xpm_file_to_image(mlx.ptr, "./wall.xpm", &mlx.img_width, &mlx.img_height);
		mlx.img_p = mlx_xpm_file_to_image(mlx.ptr, "./ralph.xpm", &mlx.img_width, &mlx.img_height);
		mlx.img_c = mlx_xpm_file_to_image(mlx.ptr, "./trophy.xpm", &mlx.img_width, &mlx.img_height);
		mlx.img_e = mlx_xpm_file_to_image(mlx.ptr, "./door.xpm", &mlx.img_width, &mlx.img_height);
		// mlx_key_hook(mlx.win, key_hook, (void *)&mlx);
		mlx_loop_hook(mlx.ptr, put_elements_positions, (void *)&mlx);
		mlx_loop(mlx.ptr);
	}
	else
		ft_exit("Not the right number of parameters !");
	return 0;
}