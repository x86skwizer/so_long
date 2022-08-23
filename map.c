/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 00:35:19 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/23 03:38:46 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_line(char *line, int len, int *player, int *exitvar)
{
	int	i;

	i = 0;
	if (line[0] != '1' || line[len - 1] != '1')
		return (-1);
	while (line[i] && i < len)
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C'
			&& line[i] != 'E' && line[i] != 'P')
			return (-1);
		if (read_player_exit(line, i, player, exitvar) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	check_wall(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] != '1')
			return (-1);
		index++;
	}
	return (0);
}

int	check_map_file(char *av)
{
	char	*ext;
	int		status;
	int		fd;

	ext = ft_substr(av, ft_strlen(av) - 4, 4);
	status = ft_strncmp(ext, ".ber", ft_strlen(ext));
	free(ext);
	fd = open(av, O_RDONLY);
	if (status != 0 || fd == -1)
	{
		ft_printf("ERROR : Map name incorrect !\n");
		exit(-1);
	}
	return (fd);
}

void	draw_map(t_space *env)
{
	char	*tmp;

	if (env->len == 0)
		env->len = count_line(env->line);
	else if (env->len != count_line(env->line))
	{
		free(env->saved_lines);
		free(env->line);
		ft_exit("ERROR : Invalid line !");
	}
	env->ret = check_line(env->line, env->len, &env->p_status, &env->e_status);
	if (env->ret == -1)
	{
		free(env->saved_lines);
		free(env->line);
		ft_exit("ERROR : Invalid map structure !");
	}
	tmp = ft_strjoin(env->saved_lines, env->line);
	free(env->saved_lines);
	free(env->line);
	env->saved_lines = tmp;
	env->line = NULL;
	env->counter++;
}

char	**map_valid_dimension(char *av, t_data *mlx)
{
	t_space	env;

	env.counter = 0;
	env.p_status = 0;
	env.len = 0;
	env.saved_lines = ft_strdup("");
	env.fd = check_map_file(av);
	while (1)
	{
		env.line = get_next_line(env.fd);
		if (!env.line)
			break ;
		draw_map(&env);
	}
	check_len(env);
	env.map = ft_split(env.saved_lines, '\n');
	free(env.saved_lines);
	if (check_wall(env.map[0]) || check_wall(env.map[env.counter - 1]))
		free_env(env);
	mlx->i = env.len;
	mlx->j = env.counter;
	return (env.map);
}
