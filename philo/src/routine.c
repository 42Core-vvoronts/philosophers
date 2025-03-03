/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:03 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 19:46:55 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_thread *philo)
{
	printf("%d: is sleeping\n", philo->id);
	usleep(philo->time_to_sleep);

}
void	thinking(t_thread *philo)
{
	printf("%d: is thinking\n", philo->id);
}

void	eating(t_thread *philo)
{
	// Lock forks
	pthread_mutex_lock(&philo->rfork);
	printf("%d: has taken right fork\n", philo->id);

	if (philo->dining->number == 1)
	{
		pthread_mutex_unlock(&philo->rfork);
		philo->dead = true;
		usleep(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(&philo->lfork);
	printf("%d: has taken left fork\n", philo->id);

	pthread_mutex_lock(&philo->meallock);
	printf("%d: is eating\n", philo->id);
	usleep(philo->time_to_eat);
	philo->last = get_current_time();
	philo->meals++;
	pthread_mutex_unlock(&philo->meallock);
	
	// Unlock forks
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_unlock(&philo->lfork);
}

bool	everyone_alive(t_ctx *dining)
{
	t_thread	*philo;

	philo = dining->philos;
	pthread_mutex_lock(&philo->deadlock);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(&philo->deadlock);
		return (false);	
	}
	pthread_mutex_unlock(&philo->deadlock);
	return (true);
}

void	*routine(void *arg)
{
	t_thread	*philo;
	t_ctx		*dining;

	philo = (t_thread *)arg;
	dining = philo->dining;
	while (everyone_alive(dining)) 
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return NULL;
}
