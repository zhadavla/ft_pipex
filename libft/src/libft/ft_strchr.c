/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:44:03 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/15 16:57:52 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * 	Searches for the first occurrence of the character {c} (an unsigned char) 
 *	in the string pointed to by the argument {s}.
*/
char	*ft_strchr(const char *s, int c)
{
	if (*s == (char )c)
		return ((char *)s);
	while (*(s++))
		if (*(char *)s == (char )c)
			return ((char *)s);
	return (NULL);
}
