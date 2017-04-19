/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:53:36 by kandreyc          #+#    #+#             */
/*   Updated: 2017/04/19 17:36:13 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#define FUNC	fractol->f

float		map(float cur, float r_min, float r_max, float min_max_i[2])
{
	float	i_min;
	float	i_max;
	float	delta;

	delta = 0;
	i_min = min_max_i[0];
	i_max = min_max_i[1];
	if (i_min < 0 && i_max > 0)
		delta = (fabs(i_min) + i_max) / (r_max - r_min);
	else
		delta = ((i_max > i_min) ?
			(i_max - i_min) : (i_min - i_max)) / (r_max - r_min);
	return (i_min + (delta * cur));
}

void		scale(t_session *session)
{
	double	x;
	double	y;

	x = map(MOUSE_X, 0, WIDTH, MIN_MAX_CX);
	y = map(MOUSE_Y, 0, HEIGHT, MIN_MAX_CY);
	MIN_CX = (MIN_CX * SCALE) + (x * (1 - SCALE));
	MIN_CY = (MIN_CY * SCALE) + (y * (1 - SCALE));
	MAX_CX = (MAX_CX * SCALE) + (x * (1 - SCALE));
	MAX_CY = (MAX_CY * SCALE) + (y * (1 - SCALE));
}

void		*render(void *p)
{
	t_fractol	*fractol;

	fractol = (t_fractol *)p;
	Y = fractol->thread;
	FUNC(fractol, 3);
	while (Y < T_HEIGHT - 1)
	{
		X = 0;
		while (X < T_WIDTH - 1)
		{
			FUNC(fractol, 1);
			N = -2;
			while (FUNC(fractol, 2) == 1)
				N++;
			pixel(fractol);
			X++;
		}
		Y += (T_THREADS - 1);
	}
	pthread_exit(NULL);
	return (p);
}

void		pre_render(t_session *session)
{
	int				i;

	i = -1;
	(SCALE != 1) ? scale(session) : 0;
	TID = (pthread_t *)malloc(sizeof(pthread_t) * (THREADS + 1));
	while (++i < THREADS)
		pthread_create(&(TID[i]), NULL, render, &(session->fractol[i]));
	i = 0;
	while (i < THREADS)
		pthread_join(TID[i++], NULL);
	SCALE = 1;
}

void		reimage(t_session *session, int flag)
{
	new_image(session);
	(flag == 0) ? pre_render(session) : line_it(*session->tree, 90, 0);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	mlx_destroy_image(MLX, IMG);
}
