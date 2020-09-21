/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:42:33 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:12:16 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memchr() function scans the initial n bytes of the memory area
** pointed to by s for the first instance of c.  Both c and the bytes of
** the memory area pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned const char	*p;
	unsigned char 		aux;

	i = 0;
	aux = (unsigned char)c;
	p = (unsigned const char *)s;
	while (*p != aux && i < n - 1)
	{
		p++;
		i++;
	}
	if (i + 1 == n)
		return (0);
	return ((void *)p);
}
