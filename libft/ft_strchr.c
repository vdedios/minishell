/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-dios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:50:27 by vde-dios          #+#    #+#             */
/*   Updated: 2019/11/18 12:21:23 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The strchr() function returns a pointer to the first occurrence of
** the character c in the string s.
*/

char	*ft_strchr(const char *s, int c)
{
	unsigned const char	*p;
	unsigned char		aux;

	aux = (unsigned char)c;
	p = (unsigned const char*)s;
	while (*p)
	{
		if (*p == aux)
			return ((char *)p);
		p++;
	}
	if (aux == 0 && *p == 0)
		return ((char *)p);
	return (0);
}
