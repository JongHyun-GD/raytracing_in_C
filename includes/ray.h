/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:01:18 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/01 22:21:05 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct		s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}					t_ray;

void	ray_set(t_ray *ray, t_vec3 *s, t_vec3 *e, int nv);

#endif
