/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:21:23 by lusanche          #+#    #+#             */
/*   Updated: 2019/09/10 05:38:10 by lusanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <fcntl.h>
# include <math.h>

# define Z_SPEED 2
# define X_Y_SPEED 50
# define ZOOM_SPEED 10

struct				s_color
{
	int				red;
	int				green;
	int				blue;
};

typedef struct		s_node
{
	double			isox;
	double			isoy;
	double			plax;
	double			play;
	double			frox;
	double			froy;
	int				z;
	struct s_color	color;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*up;
	struct s_node	*down;
}					t_node;

typedef struct		s_map
{
	int				rows;
	int				cols;
	double			adj;
	double			opp;
	int				z;
	int				x;
	int				y;
	int				on;
	int				xs;
	int				ys;
	int				zoom;
	int				proj;
	int				win_heigh;
	int				win_wide;
	int				max_z;
	int				min_z;
	int				color;
}					t_map;

typedef struct		s_co
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				x0c;
	int				y0c;
	int				x1c;
	int				y1c;
}					t_co;

typedef struct		s_pro
{
	double			isox;
	double			isoy;
	double			plax;
	double			play;
	double			frox;
	double			froy;
}					t_pro;

typedef struct		s_colo
{
	int				curr_red;
	int				curr_green;
	int				curr_blue;
	int				r1;
	int				g1;
	int				b1;
	int				r2;
	int				g2;
	int				b2;
}					t_colo;

void				free_array(char **array);
void				print_error_and_exit(int code);
void				increase_decrease_y_coordenate(void **param, int dir);
int					deal_mouse(int button, int x, int y, void **param);
void				deal_key_vi(int key, void **param, t_map *map);
void				deal_key_v(int key, void **param, t_map *map);
void				deal_key_iv(int key, void **param, t_map *map, t_node *beg);
void				deal_key_iii(int key, void **param, t_map *map);
void				deal_key_ii(int key, void **param, t_map *map);
void				deal_key_i(int key, void **param, t_map *map);
void				free_structure(void **param);
void				free_last(t_map *map, void **param);
int					deal_key(int key, void **param);
void				get_coor_next_pixel(t_co *co, int *d, int *s, int *err);
int					calculate_channel(int percent, int a_color, int b_color);
void				get_node_b_new_colors(t_node *b, t_colo *colo, t_map *map);
void				get_node_a_new_colors(t_node *a, t_colo *colo, t_map *map);
int					currcolor_bon(int perc, t_node *a, t_node *b, void **param);
int					currcolor_nat(int perc, t_node *a, t_node *b);
int					perc_calc(int curr, int start, int end);
void				get_draw_metrics(t_co *co, int *d, int *s, int *err);
void				free_arrays_int(int *d, int *s, int *err);
void				draw_line(void **param, t_co *co, t_node *a, t_node *b);
void				increase_window(t_map *map, void **param, t_node *beg);
void				x_y_iso(t_node *a, t_node *b, void **param, t_co *co);
void				x_y_plan(t_node *a, t_node *b, void **param, t_co *co);
void				x_y_front(t_node *a, t_node *b, void **param, t_co *co);
void				draw_cols(void **param, t_node *trav, t_map *map, t_co *co);
void				draw_rows(void **param, t_node *trav, t_map *map, t_co *co);
void				draw_text_menu(void **param);
void				draw_square(void **param);
void				draw_grid(void **param);
t_node				*move_pointer_to_top_right_corner(t_node *trav);
void				open_graphic_interface(t_node *beg, t_map *map);
void				initialize_projection_helper(t_pro *p, t_map *map);
void				assign_helper(t_node *adv, t_pro *p, t_map *map);
void				assign_coordenates(t_node *trav, t_map *map);
void				get_x_y_start(t_map *map);
void				get_adjacent_and_opposite(t_map *map);
int					struct_cols_counter(t_node *trav);
int					struct_rows_counter(t_node *trav);
void				get_rows_and_cols(t_node *beg, t_map *map);
void				connect_up(t_node *prev, t_node *trav);
int					ft_atoi_hex(const char *str);
int					ft_strlen_hex(char *str);
void				copy_hex_in_channels_biarray(char *hex, char **channels);
void				initialize_channels_with_ceros(char **channels);
void				assign_color_to_node(char *hex, t_node *beg);
void				assign_data_to_node(t_node *trav, char *data, t_map *map);
t_node				*create_node(void);
int					validate_quantity_of_data_packets(char **data, int *count);
void				prepare_next_node(t_node *trav, char *data, t_map *map);
t_node				*create_list(char *line, int *count, t_map *map);
t_node				*create_structure_of_nodes(int fd, t_map *map);
int					read_file(char **av);
t_map				*initialize_map(void);

#endif
