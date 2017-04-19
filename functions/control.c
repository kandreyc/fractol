/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:52:54 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 19:13:39 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int		mouse_hook(int x, int y, t_session *session)
{
	if (x <= WIDTH && y <= HEIGHT && x > 0 && y > 0)
	{
		MOUSE_X = x;
		MOUSE_Y = y;
	}
	return (0);
}

static	int		around(t_session *session)
{
	if (KEY == 5 || KEY == 4)
		SCALE = (KEY == 5) ? 0.9 : 1.1;
	else if (KEY == 126 || KEY == 125)
	{
		MIN_CY += ((KEY == 125) ? -0.1 : 0.1);
		MAX_CY += ((KEY == 125) ? -0.1 : 0.1);
	}
	else if (KEY == 124 || KEY == 123)
	{
		MIN_CX += ((KEY == 124) ? -0.1 : 0.1);
		MAX_CX += ((KEY == 124) ? -0.1 : 0.1);
	}
	KEY = 0;
	reimage(session, 0);
	return (0);
}

static	int		mouse_control(int button, int x, int y, t_session *session)
{
	x *= 1;
	y *= 1;
	if (button == 5 || button == 4)
		KEY = (button == 5) ? 5 : 4;
	control(button, session);
	return (0);
}

void			maxiterations(t_session *session, int button, int n)
{
	if (MAX_N - n > 0 && MAX_N + n < 275)
		MAX_N += (button == 116) ? n : -n;
	else if (MAX_N - n == 0)
		MAX_N += (button == 116) ? n : 0;
	else if (MAX_N + n == 275)
		MAX_N += (button == 116) ? 0 : -n;
}

int				control(int button, t_session *session)
{
	key_define(button, session);
	if (button == 18 || button == 19)
		session->color_is = (button == 18) ? 0 : 2;
	else if (button == 20 || button == 21)
		session->color_is = (button == 20) ? 4 : 6;
	else if (button == 23 || button == 22)
		session->color_is = (button == 23) ? 8 : 10;
	else if (button == 26)
		session->color_is = 11;
	(KEY != 0 || LIVE_XY > 0)
	? mlx_loop_hook(MLX, around, session) : reimage(session, 0);
	mlx_key_hook(WIN, control, session);
	mlx_hook(WIN, 6, 0, mouse_hook, session);
	mlx_mouse_hook(WIN, mouse_control, session);
	mlx_loop(MLX);
	return (0);
}
