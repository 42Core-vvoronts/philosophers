/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:45:20 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 10:56:15 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long		nstr;

	nstr = 0;
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nstr = 10 * nstr + (*str - '0');
		str++;
	}
	if (*str)
		return (0);
	return (nstr);
}
