/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:51:34 by mnascime          #+#    #+#             */
/*   Updated: 2023/11/13 18:19:45 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "./libft/libft.h"

# define WWID 1920
# define WHEI 1080
# define SQR_SIZE 18
# define STEP 0.1
# define DOOR_MULTIP 0.35
# define MY_PI 3.141590

# define ESC 65307
# define FRONT 119
# define BACK 115
# define TOLEFT 97
# define TORIGHT 100
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

# define PRT_NORTH "NO"
# define PRT_SOUTH "SO"
# define PRT_EAST "EA"
# define PRT_WEST "WE"
# define PRT_FLOOR "F"
# define PRT_CEIL "C"
# define PRT_UP "UP"
# define PRT_LOW "LO"

typedef struct s_node	t_node;

typedef struct s_node
{
	int				*symbol;
	int				tot_cols;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		tot_rows;
}	t_list;

typedef struct s_map
{
	char	**map;
	int		tot_rows;
	int		tot_cols;
}	t_map;

enum e_map
{
	ZERO = '0',
	WALL = '1',
	SPACE = ' ',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	DOOR_UP = 'U',
	DOOR_DOWN = 'D',
};

enum e_texture
{
	NO,
	SO,
	EA,
	WE,
	UP,
	DOWN,
	F,
	C,
	TOT,
};

enum e_directions
{
	MOV_UP = 1,
	MOV_DOWN,
	MOV_LEFT,
	MOV_RIGHT,
	ROT_UP,
	ROT_DOWN,
	ROT_LEFT,
	ROT_RIGHT,
};

typedef struct s_txtrs
{
	char	**path;
	int		*color;
	int		type;
	int		levels;
}	t_txtrs;

typedef struct s_all_txtrs
{
	t_txtrs		*textures;
	int			tot_txtrs;
}	t_all_txtrs;

typedef struct s_minimap
{
	int			*x_vals;
	int			*y_vals;
}	t_minimap;

typedef struct s_vector
{
	int	xi;
	int	yi;
	int	xf;
	int	yf;
}	t_vector;

typedef struct s_ray
{
	int		x;
	int		y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	dist_x;
	double	dist_y;
	double	real_dist;
	int		xstep;
	int		ystep;
	int		side;
}	t_ray;

typedef struct s_cub3d
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	t_minimap	*minimap;
	t_vector	*player;
	int			sqr_size;
	int			move;
	int			inverted;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		direction;
	int			level;
	t_all_txtrs	*all_txtrs;
	int			map_cols;
}	t_cub3d;

// CALC PLAYER MOVS
int			check_colisions_and_move(t_cub3d *cub);

// CHECK COLISIONS
int			player_colision_x(t_cub3d *cub, double dist, int type);
int			player_colision_y(t_cub3d *cub, double dist, int type);
int			check_door_colision(t_cub3d *cub, double distx, double disty);

// DEFINE KEYS
int			quits(t_cub3d *cub);
int			in_key(t_cub3d *cub);
int			key_press(int key_pressed, t_cub3d *cub);
int			key_release(int key_pressed, t_cub3d *cub);
int			read_keys(int key_pressed, t_cub3d *cub);

// DESTROY STRUCTS
void		destroy_split(char ***split_location);
void		destroy_list(t_list *list);
void		destroy_cub(t_cub3d *cub);
void		destroy_txtrs_list(t_all_txtrs *txtrs);
void		destroy_matrix(char **mat, int tot_rows);

// DRAW MINIMAP
void		draw_paralell_hlines(t_cub3d *cub, \
t_vector *vec, int beg, int color);
void		draw_doors(t_cub3d *cub, t_map *map, double xcorr, double ycorr);
void		draw_walls(t_cub3d *cub, t_map *map, double xcorr, double ycorr);
void		position_minimap(t_vector *vec, double ycorr, double xcorr);
void		redraw_minimap(t_cub3d *cub);

// DRAW PLAYER
void		draw_player_lines(t_cub3d *cub, t_vector vec, int dist, int color);
void		draw_player(t_cub3d *cub, double ycorr, double xcorr);
int			get_player_sqr(t_cub3d *cub, int is_horiz);
int			reload_player_pos(t_cub3d *cub, int x, int y);
void		init_player_pos(t_cub3d *cub, int x, int y);

// FILL STRUCTS
char		**solo_matrix(int rows, int cols);
void		insert_map_tail(t_list *list, int *data, int len);
void		list_to_map(t_list *list, t_cub3d *cub);
void		insert_txtrs(t_cub3d **cub, char *line, int txtr_type);

// FIND SQR COORD
int			rotate_view(t_cub3d *cub);
void		get_h_vector(t_cub3d *cub, t_vector *vec, int x, int y);
void		get_v_vector(t_cub3d *cub, t_vector *vec, int x, int y);
int			get_sqr_coord(t_cub3d *cub, int xval, int yval, char is_horiz);
int			get_sqr_size(void);

//INIT STRUCTS
t_node		*init_node(void);
void		init_list(t_list *list);
int			init_cub(t_cub3d *cub);
t_all_txtrs	*init_txtrs(void);
void		init_matrix(t_cub3d *cub, int tot_rows, int tot_cols);

// MAIN DISPLAY
void		display_in_canvas(t_cub3d *cub3d);

// MAIN
int			*fill_line_of_list(char *line);
int			fill_in_cub(t_cub3d *cub, int fd);
void		display_in_canvas(t_cub3d *cub);

// PIXEL DRAWING FUNCTIONS
void		minimap_pixel_put(t_cub3d *cub, int x, int y, int color);
void		minimap_draw_line(t_cub3d *cub, t_vector *vector, int color);
void		my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color);
void		draw_line(t_cub3d *data, t_vector *vector, int color);

// RAYCASTING
void		rot_raycaster(t_cub3d *cub, double dif);
void		init_raycaster(t_cub3d *cub);
void		raycasting(t_cub3d *cub);

// STR UTILS
int			ft_isspace(int c);
int			is_only_spaces(char *str);
int			ft_str_end_trim(char *line);
char		*conv_to_txtr_text(char c);

// TOGGLE MOVS
void		add_player_mov(t_cub3d *cub, int key);
void		remove_player_mov(t_cub3d *cub, int key);
void		add_player_rot(t_cub3d *cub, int key);
void		remove_player_rot(t_cub3d *cub, int key);

// TOGGLE TEXTURES
void		change_textures(t_cub3d *cub, int x, int y);

// UTILITY PRINTS
void		print_map(t_map *map, int cols);
void		print_txtrs(t_all_txtrs *txtrs);
void		print_matrix(int **mat, int rows, int cols);
void		print_err_cub(char *msg, t_cub3d *cub);

// OTHER UTILS
void		free_mtx(char **mtx);
int			mtx_len(char **mtx);

// VALIDATE MAP
int			map_line_is_valid(char *line);
int			is_valid_elem(char *line);
void		check_map(t_cub3d *cub);
int			check_border(char **map, int i);
int			check_line_lim(char **map, int i, int j);
int			check_line_mid(char **map, int i, int j);
int			check_door(char **map, int i, int j);

#endif
