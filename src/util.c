/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:42:06 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/08 14:28:36 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "rt.h"

double      clamp(double num, double min, double max)
{
    if (num > max)
        num = max;
    else if (num < min)
        num = min;
    return (num);
}

t_vec3      mat_multi(double **mat, int mat_h, t_vec3 src)
{
    int     y;
	t_vec3	ret;

	ret = vec3_init(0.0, 0.0, 0.0);
    y = 0;
    while (y < mat_h)
    {
		ret.x += src.x * mat[y][0];
		ret.y += src.y * mat[y][1];
		ret.z += src.z * mat[y][2];
		y++;
    }
	return (ret);
}

t_vec3      rotate(char axis, t_vec3 src, double theta)
{
	if (axis == 'x')
		return (
			vec3_init(
			src.x,
			src.y * cos(theta) + src.z * -sin(theta),
			src.y * sin(theta) + src.z * cos(theta)));
	if (axis == 'y')
		return (
			vec3_init(
			src.x * cos(theta) + src.z * sin(theta),
			src.y,
			src.x * -sin(theta) + src.z * cos(theta)));
	if (axis == 'z')
		return (
			vec3_init(
			src.x * cos(theta) + src.y * -sin(theta),
			src.x * sin(theta) + src.y * cos(theta),
			src.z));
	return (src);
}