/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:20:44 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/19 16:11:53 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memcpy() function copies n bytes from memory area src to memory
** area dest. The memory areas must not overlap. Use memmove(3) if the
** memory areas do overlap.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*str1;
	const char	*str2;
	size_t		i;

	i = 0;
	str1 = (char *)dst;
	str2 = (const char *)src;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (str1);
}
