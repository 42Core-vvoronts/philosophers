/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:18:50 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:35:28 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	writestatus(t_thread *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->ctx->lock);
	time = gettime();
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->ctx->lock);
}
