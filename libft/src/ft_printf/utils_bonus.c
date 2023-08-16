/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:54:44 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/16 19:57:49 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_utils(char *str, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putspace(int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int	ft_putzero(int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		write(1, "0", 1);
		i++;
	}
	return (i);
}

int	ft_putsigns(t_flags *flags, t_specifiers *sp)
{
	if ((sp->d || sp->i) && flags->is_negative)
		return (ft_putstr_utils("-", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_space)
		return (ft_putstr_utils(" ", 1));
	if ((sp->d || sp->i) && !flags->is_negative && flags->is_plus)
		return (ft_putstr_utils("+", 1));
	return (0);
}
