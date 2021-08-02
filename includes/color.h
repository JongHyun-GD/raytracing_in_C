/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:24:51 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/06 20:05:24 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef int t_color;

void		color_set(t_color *c, double r, double g, double b);
double		color_get(char c, t_color color);
t_color		color_multi(double t, t_color color);
t_color		color_blend(t_color a, t_color b, t_color c);
t_color		color_plus(t_color a, t_color b);

#endif