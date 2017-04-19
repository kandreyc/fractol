/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kandreyc <kandreyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 20:35:28 by kandreyc          #+#    #+#             */
/*   Updated: 2017/03/03 18:58:40 by kandreyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int				ft_strcmp(const char *s1, const char *s2)
{
	int		k;

	k = -1;
	while (s1[++k])
		if (s1[k] != s2[k])
			break ;
	return ((unsigned char)s1[k] - (unsigned char)s2[k]);
}

static	void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static	void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

int				error(char *msg, int esc)
{
	if (esc == 1)
	{
		ft_putstr("Choose the fractal from the list:\n");
		ft_putstr("1. mandelbrot\n");
		ft_putstr("2. julia\n");
		ft_putstr("3. sunflower\n");
		ft_putstr("4. mandelCube\n");
		ft_putstr("5. tree\n");
	}
	else
		ft_putstr(msg);
	if (esc == 1 || esc == 2)
		exit(0);
	return (0);
}
