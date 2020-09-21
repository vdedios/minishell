/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:08:01 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:25:46 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** strlcat() appends string src to the end of dst.
** It will append at most dstsize - strlen(dst) - 1
** characters. It will then NUL-terminate, unless
** dstsize is 0 or the original dst string was longer
** than dstsize (in practice this should not happen as
** it means that either dstsize is incorrect or that
** dst is not a proper string)
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t l_dst;

	l_dst = ft_strlen(dst);
	j = 0;
	if (dstsize < l_dst)
		return (dstsize + ft_strlen(src));
	else
	{
		i = l_dst;
		while (src[j] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (l_dst + ft_strlen(src));
	}
}
