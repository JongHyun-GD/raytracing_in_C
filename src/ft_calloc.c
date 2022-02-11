/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongpark <jongpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:15:25 by jongpark          #+#    #+#             */
/*   Updated: 2021/01/04 17:41:29 by jongpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!(ptr = (void *)malloc(count * size)))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
