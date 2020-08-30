/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:26:02 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:30:02 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*found;

	i = 0;
	j = 0;
	found = (char*)haystack;
	if (*(needle) == '\0' || haystack == needle)
		return ((char*)haystack);
	while (found[j] && j < len)
	{
		while (found[j + i] == needle[i])
		{
			if (!needle[i])
				break ;
			i++;
		}
		if (i == ft_strlen(needle) && (i + j) < len)
			return (&found[j]);
		i = 0;
		j++;
	}
	return (0);
}
