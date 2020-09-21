/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:25:27 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:10:04 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The memmove() function copies n bytes from memory area src to memory
** area dest.  The memory areas may overlap: copying takes place as
** though the bytes in src are first copied into a temporary array that
** does not overlap src or dest, and the bytes are then copied from the
** temporary array to dest.
*/

#include "libft.h"

static void	ft_overlap(size_t len, int i, unsigned char *str_dst, unsigned const char *str_src)
{
	i = (int)(len - 1);
	while (i >= 0)
	{
		str_dst[i] = str_src[i];
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned const char	*str_src;
	unsigned char		*str_dst;
	int			i;

	i = 0;
	str_dst = (unsigned char *)dst;
	str_src = (unsigned const char *)src;
	if (!dst && !src)
		return (NULL);
	if (str_src < str_dst)
		ft_overlap(len, i, str_dst, str_src);
	else
	{
		i = 0;
		while (i < (int)len)
		{
			str_dst[i] = str_src[i];
			i++;
		}
	}
	return (dst);
}
