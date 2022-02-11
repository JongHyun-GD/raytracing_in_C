/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:16:42 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/06 20:06:38 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		color_set (t_color *c, double r, double g, double b)
{
	*c = 0;
	*c |= ((int)(r * 255) << 16);
	*c |= ((int)(g * 255) << 8);
	*c |= ((int)(b * 255));
}

double		color_get (char c, t_color color)
{
	if (c == 'r')
		color = color >> 16;
	else if (c == 'g')
		color = color >> 8;
	return ((color & 0x000000FF) / 255.0);
}

t_color		color_multi (double t, t_color color)
{
	double		r;
	double		g;
	double		b;
	t_color		ret;

	r = color_get('r', color);
	g = color_get('g', color);
	b = color_get('b', color);
	r = clamp(r * t, 0.0, 1.0);
	g = clamp(g * t, 0.0, 1.0);
	b = clamp(b * t, 0.0, 1.0);
	color_set(&ret, r, g, b);
	return (ret);
}

t_color		color_plus(t_color a, t_color b)
{
	double		r;
	double		g;
	double		bb;
	t_color		ret;

	r = clamp(color_get('r', a) + color_get('r', b), 0.0, 1.0);
	g = clamp(color_get('g', a) + color_get('g', b), 0.0, 1.0);
	bb = clamp(color_get('b', a) + color_get('b', b), 0.0, 1.0);
	color_set(&ret, r, g, bb);
	return (ret);
}

t_color		color_blend(t_color a, t_color b, t_color c)
{
	double		r;
	double		g;
	double		bb;
	t_color		ret;

	r = clamp(color_get('r', a) + color_get('r', b) + color_get('r', c), 0.0, 1.0);
	g = clamp(color_get('g', a) + color_get('g', b) + color_get('g', c), 0.0, 1.0);
	bb = clamp(color_get('b', a) + color_get('b', b) + color_get('b', c), 0.0, 1.0);
	color_set(&ret, r, g, bb);
	return (ret);
}