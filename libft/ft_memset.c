/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:20:52 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 11:56:48 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The C library function void *memset(void *str, int c, size_t n)
** copies the character c (an unsigned char) to the first n characters
** of the string pointed to, by the argument str.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		((unsigned char*)b)[i++] = c;
	return ((void*)b);
}
