/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:16:28 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 19:10:54 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include <pthread.h>

# define FLAG		session->flag
# define WIN		session->win
# define MLX		session->mlx
# define IMG		session->img
# define DATA		session->data

# define MOUSE_X	session->mouse_x
# define MOUSE_Y	session->mouse_y
# define LIVE_XY	session->mouse_live

# define WIDTH		session->width
# define HEIGHT		session->height
# define SCALE		session->scale

# define MIN_R		session->min_rgb[0]
# define MIN_G		session->min_rgb[1]
# define MIN_B		session->min_rgb[2]

# define MAX_R		session->max_rgb[0]
# define MAX_G		session->max_rgb[1]
# define MAX_B		session->max_rgb[2]

# define END		session->end_bbp_sizeline[0]
# define BBP		session->end_bbp_sizeline[1]
# define SIZELINE	session->end_bbp_sizeline[2]

# define X			fractol->x
# define Y			fractol->y
# define K			fractol->k

# define MIN_X		fractol->min_x
# define MIN_Y		fractol->min_y
# define MAX_X		fractol->max_x
# define MAX_Y		fractol->max_y

# define A			fractol->abcdef[0]
# define B			fractol->abcdef[1]
# define C			fractol->abcdef[2]
# define D			fractol->abcdef[3]
# define E			fractol->abcdef[4]
# define F			fractol->abcdef[5]

# define A0			fractol->a0
# define B0			fractol->b0

# define N			fractol->n
# define MAX_N		session->max_n

# define TMP		fractol->tmp

# define MIN_MAX_CX	session->min_max_cx
# define MIN_CX		session->min_max_cx[0]
# define MAX_CX		session->min_max_cx[1]

# define MIN_MAX_CY	session->min_max_cy
# define MIN_CY		session->min_max_cy[0]
# define MAX_CY		session->min_max_cy[1]

# define TID		session->tid
# define THREADS	session->threads

# define RED		fractol->rgb[0]
# define GREEN		fractol->rgb[1]
# define BLUE		fractol->rgb[2]

# define KEY		session->key

# define T_MIN_R			(fractol->min_rgb[0])
# define T_MIN_G			(fractol->min_rgb[1])
# define T_MIN_B			(fractol->min_rgb[2])

# define T_MAX_R			(fractol->max_rgb[0])
# define T_MAX_G			(fractol->max_rgb[1])
# define T_MAX_B			(fractol->max_rgb[2])

# define T_WIDTH			*(fractol->width)
# define T_HEIGHT			*(fractol->height)
# define T_SCALE			*(fractol->scale)
# define T_MIN_MAX_CX		*(fractol->min_max_cx)
# define T_MIN_MAX_CY		*(fractol->min_max_cy)
# define T_MOUSE_X			*(fractol->mouse_x)
# define T_MOUSE_Y			*(fractol->mouse_y)
# define T_LIVE_XY			*(fractol->mouse_live)
# define T_SEZELINE			*(fractol->sizeline)
# define T_MAX_N			*(fractol->max_n)

# define T_MIN_CX			*(fractol->min_max_cx[0])
# define T_MAX_CX			*(fractol->min_max_cx[1])
# define T_MIN_CY			*(fractol->min_max_cy[0])
# define T_MAX_CY			*(fractol->min_max_cy[1])
# define T_THREADS			*(fractol->quantity_threads)
# define T_COLOR_IS			*(fractol->color_is)

typedef struct		s_tree
{
	float			x;
	float			y;
	float			k;
	int				*width;
	int				*height;
	float			min_x;
	float			min_y;
	float			max_x;
	float			max_y;
	float			len;
	float			max_len;
	float			phi;
	float			brunch;
	float			mouse_x;
	float			mouse_y;

	float			*scale;
	char			**data;
	unsigned char	rgb[3];
	unsigned char	*min_rgb[3];
	unsigned char	*max_rgb[3];
	int				*sizeline;
}					t_tree;

typedef struct		s_fractol
{
	int				thread;
	float			x;
	float			y;
	float			k;
	float			min_x;
	float			min_y;
	float			max_x;
	float			max_y;
	float			abcdef[6];
	float			a0;
	float			b0;
	int				(*f)();
	int				fractol_is[0];
	float			*tmp;
	int				*quantity_threads;
	float			*mouse_live;
	float			*mouse_x;
	float			*mouse_y;
	float			**min_max_cx;
	float			**min_max_cy;
	unsigned char	min_rgb[3];
	unsigned char	max_rgb[3];
	int				*width;
	int				*height;
	float			*scale;
	int				*color;
	int				*color_is;
	int				n;
	int				*max_n;
	char			**data;
	unsigned char	rgb[3];
	int				*sizeline;
}					t_fractol;

typedef struct		s_session
{
	int				key;
	void			*win;
	void			*mlx;
	void			*img;
	char			*data;
	float			mouse_x;
	float			mouse_y;
	float			mouse_live;
	int				max_n;

	int				flag;
	float			scale;
	int				width;
	int				height;
	int				end_bbp_sizeline[3];
	float			*min_max_cx;
	float			*min_max_cy;
	unsigned char	min_rgb[3];
	unsigned char	max_rgb[3];
	int				threads;
	pthread_t		*tid;
	t_fractol		*fractol;
	t_tree			*tree;
	int				*color;
	int				color_is;
	int				tree_flag;
}					t_session;

void				make_tree(t_session *session);
int					tree_control(int button, t_session *session);
void				line_it(t_tree tree, float phi, int i);
t_session			*new_fractol(int threads, int (*f)(), int flag);
void				key_define(int button, t_session *session);
void				in_cube(float *a, float *b, float *c, float *d);
void				in_square(float *a, float *b);
void				maxiterations(t_session *session, int button, int n);
void				straight(t_tree *fractol);
int					cube_mandelbrot(t_fractol *fractol, int flag);
int					sunflower(t_fractol *fractol, int flag);
int					mandelbrot(t_fractol *fractol, int flag);
int					julia(t_fractol *fractol, int flag);
void				scale(t_session *session);
int					control(int button, t_session *session);
void				reimage(t_session *session, int flag);
void				pre_render(t_session *session);
void				*render(void *p);
void				new_image(t_session *session);
void				pixel(t_fractol *fractol);
void				pixel_to_image(t_tree *fractol, int x, int y);
int					error(char *msg, int esc);
int					ft_strcmp(const char *s1, const char *s2);
float				map
					(float cur, float r_min, float r_max, float min_max_i[2]);

#endif
