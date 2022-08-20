/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 00:44:55 by yamrire           #+#    #+#             */
/*   Updated: 2022/08/20 04:40:42 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include "./includes/get_next_line.h"
# include "./includes/libftprintf.h"

typedef struct s_data
{
	void	*ptr;
	void	*win;
	void	*img_p;
	void	*img_c;
	void	*img_e;
	void	*img_w;
	void	*img_f;
	int		win_width;
	int		win_height;
	int		img_width;
	int		img_height;
	int		n_p;
	int		x_p;
	int		y_p;
	int		i;
	int		j;
	char	**map;
	int		move;
	int		collect;
}	t_data;

typedef struct s_space
{
	char	**map;
	char	*saved_lines;
	char	*line;
	int		fd;
	int		len;
	int		p_status;
	int		e_status;
	int		ret;
	int		counter;
}	t_space;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	move_right(t_data *mlx);
void	move_down(t_data *mlx);
void	move_left(t_data *mlx);
void	move_up(t_data *mlx);
void	ft_exit(char *message);
int		count_line(char *s);
void	save_line(char **dist, char *line);
int		check_line(char *line, int len, int *player, int *exitvar);
int		check_wall(char *line);
int		check_map_file(char *av);
void	initialize_map(t_space *env, char *av);
char	**map_valid_dimension(char *av, t_data *mlx);
int		collect_search(t_data *mlx, char c);
void	ft_mlx(t_data *mlx);
void	load_image(t_data *mlx, int *i, int *j);
int		read_player_exit(char *line, int i, int *player, int *exitvar);

#endif