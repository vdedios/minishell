/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:49:35 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 16:00:00 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strdup() function allocates sufficient memory for
** a copy of the string s1, does the copy, and returns a
** pointer to it.  The pointer may subsequently be
** used as an argument to the function free(3)
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;

	if (!(cpy = (char *)
		malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(cpy, s1, ft_strlen(s1) + 1);
	return (cpy);
}
