/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:17:56 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 19:17:19 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			new_image(t_session *session)
{
	END = 0;
	BBP = 32;
	IMG = mlx_new_image(MLX, WIDTH, HEIGHT);
	DATA = mlx_get_data_addr(IMG, &BBP, &SIZELINE, &END);
}

static	void	color_or_not(t_fractol *fractol)
{
	int		color;

	color = (fractol->color[N % 10]);
	if (T_COLOR_IS != 11)
	{
		T_MIN_R = ((fractol->color[T_COLOR_IS] & 0xFF0000) >> 16);
		T_MIN_G = ((fractol->color[T_COLOR_IS] & 0xFF00) >> 8);
		T_MIN_B = ((fractol->color[T_COLOR_IS] & 0xFF));
		T_MAX_R = ((fractol->color[T_COLOR_IS + 1] & 0xFF0000) >> 16);
		T_MAX_G = ((fractol->color[T_COLOR_IS + 1] & 0xFF00) >> 8);
		T_MAX_B = ((fractol->color[T_COLOR_IS + 1] & 0xFF));
	}
	else
	{
		T_MIN_R = ((color & 0xFF0000) >> 16);
		T_MIN_G = ((color & 0xFF00) >> 8);
		T_MIN_B = ((color & 0xFF));
		T_MAX_R = ((color & 0xFF0000) >> 16);
		T_MAX_G = ((color & 0xFF00) >> 8);
		T_MAX_B = ((color & 0xFF));
	}
}

static	void	colorize(t_fractol *fractol)
{
	if ((X <= T_WIDTH) && (Y <= T_HEIGHT) && (X > 0) && (Y > 0))
	{
		if (N == T_MAX_N || N < 1)
		{
			RED = 0;
			GREEN = 0;
			BLUE = 0;
		}
		else
		{
			color_or_not(fractol);
			RED = (T_MIN_R + (((T_MAX_R - T_MIN_R) * N) / T_MAX_N));
			GREEN = (T_MIN_G + (((T_MAX_G - T_MIN_G) * N) / T_MAX_N));
			BLUE = (T_MIN_B + (((T_MAX_B - T_MIN_B) * N) / T_MAX_N));
		}
	}
}

void			pixel(t_fractol *fractol)
{
	int		i;

	i = (Y * T_SEZELINE) + (X * 4);
	colorize(fractol);
	(*fractol->data)[i] = BLUE;
	(*fractol->data)[i + 1] = GREEN;
	(*fractol->data)[i + 2] = RED;
}
