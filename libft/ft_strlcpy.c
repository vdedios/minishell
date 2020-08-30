/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:38:49 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:22:53 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src || !dest)
		return (0);
	i = ft_strlen(src);
	if (size == 0)
		return (i);
	while (j < size - 1 && src[j])
	{ 
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (i);
}
