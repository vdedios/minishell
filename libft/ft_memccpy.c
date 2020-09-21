/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:09:30 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/19 16:31:18 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memccpy() function copies no more than n bytes from memory area
** src to memory area dest, stopping when the character c is found.
*/

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*str1;
	unsigned const char	*str2;
	size_t			i;
	unsigned char		aux;
	
	i = 0;
	aux = (unsigned char)c;
	str1 = (unsigned char *)dst;
	str2 = (unsigned const char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n && str2[i] != aux)
	{
		str1[i] = str2[i];
		dst++;
		i++;
	}
	if (i != n)
	{
		str1[i] = str2[i];
		return (dst + 1);
	}	
	return (0);
}
