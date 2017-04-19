/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:08:51 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 18:55:47 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			julia(t_fractol *fractol, int flag)
{
	(flag == 1) ? A = map(X, 0, T_WIDTH, T_MIN_MAX_CX) : 0;
	(flag == 1) ? B = map(Y, 0, T_HEIGHT, T_MIN_MAX_CY) : 0;
	(flag == 1 && T_LIVE_XY == 0) ? A0 = -0.8 : 0;
	(flag == 1 && T_LIVE_XY == 0) ? B0 = 0.156 : 0;
	if (flag == 3 && T_LIVE_XY == 1)
		A0 = map(T_MOUSE_X, 0, T_WIDTH, T_MIN_MAX_CX);
	if (flag == 3 && T_LIVE_XY == 1)
		B0 = map(T_MOUSE_Y, 0, T_HEIGHT, T_MIN_MAX_CY);
	if (flag == 2)
	{
		in_square(&A, &B);
		A += A0;
		B += B0;
		return ((A * A + B * B <= 4 && N < T_MAX_N) ? 1 : 0);
	}
	return (0);
}

int			mandelbrot(t_fractol *fractol, int flag)
{
	(flag == 1) ? A = map(X, 0, T_WIDTH, T_MIN_MAX_CX) : 0;
	(flag == 1) ? B = map(Y, 0, T_HEIGHT, T_MIN_MAX_CY) : 0;
	(flag == 1 && T_LIVE_XY == 0) ? A0 = A : 0;
	(flag == 1 && T_LIVE_XY == 0) ? B0 = B : 0;
	if (flag == 3 && T_LIVE_XY == 1)
		A0 = map(T_MOUSE_X, 0, T_WIDTH, T_MIN_MAX_CX);
	if (flag == 3 && T_LIVE_XY == 1)
		B0 = map(T_MOUSE_Y, 0, T_HEIGHT, T_MIN_MAX_CY);
	if (flag == 2)
	{
		in_square(&A, &B);
		A += A0;
		B += B0;
		return ((A * A + B * B <= 4 && N < T_MAX_N) ? 1 : 0);
	}
	return (0);
}

int			cube_mandelbrot(t_fractol *fractol, int flag)
{
	(flag == 1) ? A = map(X, 0, T_WIDTH, T_MIN_MAX_CX) : 0;
	(flag == 1) ? B = map(Y, 0, T_HEIGHT, T_MIN_MAX_CY) : 0;
	(flag == 1 && T_LIVE_XY == 0) ? A0 = A : 0;
	(flag == 1 && T_LIVE_XY == 0) ? B0 = B : 0;
	if (flag == 3 && T_LIVE_XY == 1)
		A0 = map(T_MOUSE_X, 0, T_WIDTH, T_MIN_MAX_CX);
	if (flag == 3 && T_LIVE_XY == 1)
		B0 = map(T_MOUSE_Y, 0, T_HEIGHT, T_MIN_MAX_CY);
	if (flag == 2)
	{
		in_cube(&A, &B, &A, &B);
		A += A0;
		B += B0;
		return ((A * A + B * B <= 4 && N < T_MAX_N) ? 1 : 0);
	}
	return (0);
}

int			sunflower(t_fractol *fractol, int flag)
{
	float	tmp;

	(flag == 1) ? A = map(X, 0, T_WIDTH, T_MIN_MAX_CX) : 0;
	(flag == 1) ? B = map(Y, 0, T_HEIGHT, T_MIN_MAX_CY) : 0;
	(flag == 3 && T_LIVE_XY == 1) ?
	A0 = map(T_MOUSE_X, 0, T_WIDTH, T_MIN_MAX_CX) : 0;
	(flag == 3 && T_LIVE_XY == 1) ?
	B0 = map(T_MOUSE_Y, 0, T_HEIGHT, T_MIN_MAX_CY) : 0;
	if (flag == 2)
	{
		in_square(&A, &B);
		in_cube(&A, &B, &C, &D);
		E = ((C - 1) * A) + (D * D) +
		((T_LIVE_XY == 1 || T_LIVE_XY == 2) ? A0 : 0);
		F = ((C - 1) * B) + (D * A) +
		((T_LIVE_XY == 1 || T_LIVE_XY == 2) ? B0 : 0);
		tmp = 100 * (A * A) + 3 * (B * B);
		E = (T_LIVE_XY == 1 || T_LIVE_XY == 2) ? (E * E) : E;
		F = (T_LIVE_XY == 1 || T_LIVE_XY == 2) ? (F * F) : F;
		tmp = (fabs(E + F)) / tmp;
		return ((tmp <= 4 && N < T_MAX_N) ? 1 : 0);
	}
	return (0);
}
