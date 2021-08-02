/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:51:31 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/08 13:57:58 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "rt.h"

double      clamp(double num, double min, double max);
t_vec3      rotate(char axis, t_vec3 src, double theta);

#endif