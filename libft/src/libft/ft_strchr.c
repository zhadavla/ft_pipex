/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:44:03 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/16 19:57:49 by vzhadan          ###   ########.fr       */
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
