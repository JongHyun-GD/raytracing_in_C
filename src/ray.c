/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:20:00 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/06 17:40:29 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec3.h"

void	ray_set(t_ray *ray, t_vec3 *s, t_vec3 *e, int nv)
{
	ray->pos.x = s->x;
	ray->pos.y = s->y;
	ray->pos.z = s->z;
	ray->dir.x = e->x - s->x;
	ray->dir.y = e->y - s->y;
	ray->dir.z = e->z - s->z;
	if (nv)
		ray->dir = vec3_normalize(ray->dir);
}
