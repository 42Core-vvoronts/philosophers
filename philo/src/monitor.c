/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:14:44 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 19:32:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	everyone_full(t_thread *philos, t_ctx *dining)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	if (philos[i].musteat == 0)
		return (false);
	while (philos[i].id)
	{
		if (pthread_mutex_lock(&philos[i].meallock) != SUCCESS)
			errexit(FAIL, "pthread_mutex_lock", dining);
		if (philos[i].meals < philos[i].musteat)
			full++;
		if (pthread_mutex_unlock(&philos[i].meallock) != SUCCESS)
			errexit(FAIL, "pthread_mutex_unlock", dining);
		i++;
	}
	if (full == dining->number)
		return (true);
	return (false);	
}

bool	someone_dead(t_thread *philos, t_ctx *dining)
{
	int	i;

	i = 0;
	while (philos[i].id)
	{
		if (pthread_mutex_lock(&philos[i].deadlock) != SUCCESS)
			errexit(FAIL, "pthread_mutex_lock", dining);
		if (philos[i].dead == true)
		{
			printf("%d: died\n", philos[i].id);
			if (pthread_mutex_unlock(&philos[i].deadlock) != SUCCESS)
				errexit(FAIL, "pthread_mutex_unlock", dining);
			return (true);
		}
		if (pthread_mutex_unlock(&philos[i].deadlock) != SUCCESS)
			errexit(FAIL, "pthread_mutex_unlock", dining);
		i++;
	}
	return (false);
	
}

void	*monitor(void *arg)
{
	t_ctx	*dining;

	dining = (t_ctx *)arg;
	while (true)
	{
		if (someone_dead(dining->philos, dining) == true 
			|| everyone_full(dining->philos, dining) == true)
			break;
	}
	return (NULL);
}

