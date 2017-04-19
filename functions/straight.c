/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   straight.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:07:52 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/02 16:34:25 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

#define DELTA_Y		(fabs((MAX_Y - MIN_Y)) / fabs((MAX_X - MIN_X)))
#define DELTA_X		(fabs((MAX_X - MIN_X)) / fabs((MAX_Y - MIN_Y)))
#define SCREEN		X < T_WIDTH && Y < T_HEIGHT && X >= 0 && Y >= 0

void	pixel_to_image(t_tree *fractol, int x, int y)
{
	int		i;

	RED = 255;
	GREEN = 255;
	BLUE = 255;
	i = (y * T_SEZELINE) + (x * 4);
	(*fractol->data)[i] = BLUE;
	(*fractol->data)[i + 1] = GREEN;
	(*fractol->data)[i + 2] = RED;
}

void	straight(t_tree *fractol)
{
	X = MIN_X;
	Y = MIN_Y;
	if (MIN_X == MAX_X)
		while (Y != MAX_Y)
		{
			(SCREEN) ? pixel_to_image(fractol, X, Y) : 0;
			Y = (MIN_Y < MAX_Y) ? Y + 1 : Y - 1;
		}
	else if ((K = DELTA_Y) <= 1)
		while (X != MAX_X)
		{
			Y = (MIN_Y < MAX_Y) ? Y + K : Y - K;
			(SCREEN) ? pixel_to_image(fractol, X, Y) : 0;
			X = (MIN_X < MAX_X) ? X + 1 : X - 1;
		}
	else if ((K = DELTA_X) <= 1)
		while (Y != MAX_Y)
		{
			X = (MIN_X < MAX_X) ? X + K : X - K;
			(SCREEN) ? pixel_to_image(fractol, X, Y) : 0;
			Y = (MIN_Y < MAX_Y) ? Y + 1 : Y - 1;
		}
}
