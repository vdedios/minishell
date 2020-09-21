/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:01:18 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 16:01:16 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strchr() function returns a pointer to the last occurrence of
** the character c in the string s.
*/

char	*ft_strrchr(const char *s, int c)
{
	int	j;
	int 	i;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c)
			j++;
		else
			j = 0;
		i++;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	if (j == i)
		return (0);
	return ((char *)(s - j- 1));
}
