/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 15:11:42 by dbolilyi          #+#    #+#             */
/*   Updated: 2018/08/23 15:50:35 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __WOLF_H
# define __WOLF_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <math.h>
# include <time.h>
# include <pthread.h>
# include <signal.h>

# define WINDOW_X 1300
# define WINDOW_Y 700
# define THREADS 4
# define MOVING_SPEED 7
# define ROTATE_SPEED 3
# define SENSIVITY 5
# define ENEMY_SPEED 3
# define START_PLAYER_ROT 180
# define BSZ 100

typedef struct	s_map
{
	char	**map;
	int		y;
	int		x;
}				t_map;

typedef struct	s_map_list
{
	char				*s;
	struct s_map_list	*next;
}				t_map_list;

typedef struct	s_view
{
	int		bpp;
	int		size_line;
	int		endian;
	int		fullbpp;
	int		fullsize_line;
	int		fullendian;
	int		text_fill;
	int		door_plus;
	int		gun_status;
	int		gun_size;
}				t_view;

typedef struct	s_enemy
{
	int				x;
	int				y;
	int				damage;
	int				health;
	int				status;
	int				time;
	char			flag;
	struct s_enemy	*next;
}				t_enemy;

typedef struct	s_player
{
	int		x;
	int		y;
	int		rot;
	int		angle;
	int		sx;
	int		sy;
	int		health;
	int		score;
	int		lives;
	int		damage;
}				t_player;

typedef struct	s_tex
{
	void	*ptr;
	char	*data;
	int		w;
	int		h;
	int		bpp;
	int		szln;
	int		endian;
}				t_tex;

typedef struct	s_textures
{
	t_tex	t1;
	t_tex	t2;
	t_tex	t3;
	t_tex	t4;
	t_tex	floor;
	t_tex	ceil;
	t_tex	door;
	t_tex	barrel;
	t_tex	enemy[10];
	t_tex	gun[3];
	t_tex	bar;
	t_tex	key;
	t_tex	p[3];
	t_tex	numb[10];
	t_tex	miss;
	t_tex	dead[3];
	t_tex	pause;
}				t_textures;

typedef struct	s_get_ray
{
	int		dist;
	char	type;
	int		rx;
	int		ry;
	float	k;
	int		tmp;
}				t_get_ray;

typedef struct	s_flags
{
	char		shoot;
	int			shoot_time;
	char		door;
	t_get_ray	d;
	char		rotright;
	char		rotleft;
	char		forward;
	char		back;
	char		right;
	char		left;
	char		miss;
	char		pause;
	char		dead;
	int			dead_time;
}				t_flags;

typedef struct	s_sounds
{
	int		environment;
	int		step;
	int		shot;
	int		door;
	int		enemyshot;
}				t_sounds;

typedef struct	s_mlx
{
	char		*avail;
	void		*init;
	void		*win;
	void		*img_ptr;
	char		*img_data;
	int			st;
	int			end;
	int			status;
	t_view		v;
	t_map		m;
	t_player	p;
	t_textures	t;
	t_enemy		*e;
	t_flags		f;
	int			still_pressed;
	char		move;
	int			t1;
	int			t2;
	int			start_mousex;
	t_sounds	s;
}				t_mlx;

typedef struct	s_add_enemy
{
	t_enemy	*e;
	float	delta;
	int		size;
	int		len;
	int		rot;
	int		minrot;
	int		maxrot;
}				t_add_enemy;

typedef struct	s_get_enemy
{
	t_enemy	*e;
	int		sz;
	float	delta;
	int		len;
}				t_get_enemy;

typedef struct	s_element
{
	char				type;
	t_add_enemy			a;
	int					rx;
	int					ry;
	char				last_changed;
	struct s_element	*next;
}				t_element;

typedef struct	s_check_enemy
{
	t_add_enemy	a;
	t_get_ray	r;
	int			len;
	int			rlen;
}				t_check_enemy;

typedef struct	s_add_el
{
	int		rx;
	int		ry;
	float	k;
	float	b;
}				t_add_el;

typedef struct	s_draw2
{
	float		ang;
	char		xdir;
	char		ydir;
	int			i;
	int			nx;
	int			ny;
	char		b;
	int			tmp;
	int			tmp2;
	int			tmp3;
	float		tmp4;
	float		tmp5;
	float		tmp6;
	float		tmp7;
	float		tmp8;
	float		tmp9;
	char		last_changed;
	char		prev_last;
	int			count_els;
	t_element	*els;
	t_add_el	add_el;
	int			rx;
	int			ry;
	float		k;
	float		bb;
}				t_draw2;

typedef void	(*t_iw_func) (t_mlx * iw);

typedef struct	s_brez
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			k;
	int			color;
	t_mlx		*iw;
}				t_brez;

typedef struct	s_draw_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_draw_line;

void			pixel_put_img(t_mlx *iw, int x, int y, int color);
void			print_brez(t_brez *b, int d, int d1, int d2);
void			brez_line(t_mlx *iw, t_draw_line line, int color);
void			add_enemy(t_mlx *iw, int x, int y);
int				check_string_map_i(char *s, t_mlx *iw, char *start, int i);
int				check_string_map(char *s, t_mlx *iw, char *start);
void			add_map_line(char *s, t_map_list **m, t_mlx *iw);
void			clear_map_lst(t_map_list *m);
int				get_max_map_len(t_mlx *iw, t_map_list *m);
void			rewrite_map(t_mlx *iw, t_map_list *m);
void			free_map(t_mlx *iw);
int				read_map(int fd, t_mlx *iw);
int				check4err(int argc, char **argv);
void			get_dir(t_draw2 *d);
float			get_k(float ang);
t_draw2			get_start_d(t_mlx *iw, int i, float ang);
void			get_r(t_mlx *iw, int i, t_get_ray *r, t_draw2 *d);
void			get_ray(t_mlx *iw, int i, t_get_ray *r, float ang);
t_tex			get_tex(t_mlx *iw, t_draw2 *d);
int				draw_wall(t_mlx *iw, int rx, int ry, t_draw2 *d);
void			draw_floor_ceil(t_mlx *iw, int rx, int ry, t_draw2 *d);
void			draw_enemy(t_mlx *iw, t_add_enemy *a, int x);
int				get_enemy_rot(t_mlx *iw, t_enemy *e);
void			get_min_max_enemy_rot(t_mlx *iw, t_add_enemy *a, int ang);
void			draw_el(t_mlx *iw, t_draw2 *d, t_element *(*el), t_tex tex);
int				draw_el_get_pl(t_mlx *iw, t_element *el, t_tex *tex);
void			draw_elements(t_mlx *iw, t_draw2 *d, int rx, int ry);
t_element		*add_element2(t_draw2 *d);
void			add_element(t_element **start, t_draw2 *d, t_mlx *iw);
void			free_elements(t_element *els);
void			delete_el(t_element **start, t_element *el);
int				get_el_len(t_mlx *iw, t_element *el);
void			insert_el_after(t_element *dest, t_element *el);
void			add_enemies_to_elements2(t_draw2 *d,
					t_element *start, t_mlx *iw);
void			add_enemies2(t_element **start, t_enemy **tmp, t_element *cr);
void			add_enemies(t_draw2 *d, t_mlx *iw);
void			draw2(t_draw2 *d, t_mlx *iw);
void			draw3(t_draw2 *d, t_mlx *iw);
void			draw_try_add_el(t_draw2 *d, t_mlx *iw);
void			draw(t_mlx *iw);
void			threads_draw(t_mlx *iw);
void			draw_gun(t_mlx *iw);
void			draw_numb(t_mlx *iw, int numb, int x);
void			draw_bar(t_mlx *iw);
void			update(t_mlx *iw);
void			check_collisions(t_mlx *iw, t_draw2 *d);
void			move(t_mlx *iw, int pl);
void			check_action(t_mlx *iw);
int				key_hook2(int keycode, t_mlx *iw);
int				key_hook(int keycode, t_mlx *iw);
int				get_enemy2(t_mlx *iw, float k, t_enemy **tmp, t_get_enemy *g);
void			get_enemy(t_mlx *iw, t_add_enemy *a, float k);
void			damage_enemy(t_mlx *iw);
void			shoot(t_mlx *iw);
void			door1(t_mlx *iw);
void			door2(t_mlx *iw);
void			check_enemy_collisions(t_mlx *iw, t_draw2 *d, t_enemy *e);
void			move_enemy(t_mlx *iw, t_enemy *e, t_check_enemy *chk);
void			check_enemy_action5(t_enemy *tmp, t_mlx *iw);
void			check_enemy_action4(t_enemy *tmp,
					t_check_enemy *chk, t_mlx *iw);
void			check_enemy_action3(t_enemy *tmp,
					t_check_enemy *chk, t_mlx *iw);
void			check_enemy_action2(t_enemy *tmp,
					t_check_enemy *chk, t_mlx *iw);
void			check_enemy_action(t_enemy *tmp, t_check_enemy *chk, t_mlx *iw);
void			check_enemies2(t_mlx *iw, t_enemy *tmp, t_check_enemy *chk);
void			check_enemies(t_mlx *iw);
int				key_unpressed(int keycode, t_mlx *iw);
void			actions(t_mlx *iw);
void			dead(t_mlx *iw);
void			pause_f(t_mlx *iw);
void			unpause_f(t_mlx *iw);
void			exit_s();
void			check_sound(t_mlx *iw);
int				loop(t_mlx *iw);
void			get_def2(t_mlx *iw);
void			get_def(t_mlx *iw);
int				exit_x(t_mlx *iw);
int				mouse_move(int x, int y, t_mlx *iw);
int				check_textures(t_mlx *iw);
void			get_textures_data(t_mlx *iw);
void			get_textures(t_mlx *iw);
int				main2(t_mlx *iw);

#endif
