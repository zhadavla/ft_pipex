/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:00:27 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/15 17:02:22 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_tmp(int fd, char *tmp);
char	*get_line(char *tmp);
char	*clean_tmp(char *tmp);
int		is_strchr(char *s, char c);

char	*ft_strjoin(char *tmp, char *buf);

#endif