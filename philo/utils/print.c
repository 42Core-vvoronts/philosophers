/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:18:50 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/13 11:16:37 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	writestatus(t_thread *philo, char *str)
{
	long	time;

	time = gettime();
	printf("%zu %ld %s\n", time, philo->id, str);
}
