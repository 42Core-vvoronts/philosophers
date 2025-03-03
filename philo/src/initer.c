/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/03 19:12:31 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	validate(char **argv, int argc)
{
	char	*msg;

	msg = NULL;
	if (argc != 5 && argc != 6)
		msg = "Invalid number of arguments";
	else if (ft_atoi(argv[1]) > MAXPH || ft_atoi(argv[1]) <= 0)
		msg = "Invalid philosophers number";
	else if (ft_atoi(argv[2]) <= 0)
		msg = "Invalid time to die";
	else if (ft_atoi(argv[3]) <= 0)
		msg = "Invalid time to eat";
	else if (ft_atoi(argv[4]) <= 0)
		msg = "Invalid time to sleep";
	else if (argv[5] && (ft_atoi(argv[5]) < 0))
		msg = "Invalid number of times each philosopher must eat";
	if (msg)
		errexit(FAIL, msg, NULL);
}

void	init_philo(t_thread *philo, char **argv, t_ctx *dining, int i)
{
	philo->id = i + 1;
	philo->meals = 0;
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		philo->musteat = ft_atoi(argv[5]);
	else
		philo->musteat = 0;

	if (pthread_mutex_init(&philo->lfork, NULL) != SUCCESS)
		errexit(FAIL, "pthread_mutex_init left fork", dining);
	if (pthread_mutex_init(&philo->rfork, NULL) != SUCCESS)
		errexit(FAIL, "pthread_mutex_init right fork", dining);

	philo->dining = dining;
}

void	init(t_ctx **dining, int argc, char **argv)
{
	int			i;
	int			code;
	t_thread	*philo;

	validate(argv, argc);
	*dining = (t_ctx *)memalloc(sizeof(t_ctx), NULL);
	(*dining)->number = ft_atoi(argv[1]);
	(*dining)->philos = (t_thread *)memalloc(sizeof(t_thread) * (*dining)->number, *dining);

	code = pthread_create(&(*dining)->waiter, NULL, monitor, *dining);
	if (code != SUCCESS)
		errexit(code, "pthread_create waiter", *dining);

	i = 0;
	while (i < (*dining)->number)
	{
		philo = &(*dining)->philos[i];
		init_philo(philo, argv, *dining, i);
		code = pthread_create(&philo->thread, NULL, routine, philo);
		if (code != SUCCESS)
			errexit(code, "pthread_create philosopher", *dining);
		i++;
	}

	i = 0;
	while (i < (*dining)->number)
	{
		code = pthread_join((*dining)->philos[i].thread, NULL);
		if (code != SUCCESS)
			errexit(code, "pthread_join philosopher", *dining);
		i++;
	}

	code = pthread_join((*dining)->waiter, NULL);
	if (code != SUCCESS)
		errexit(code, "pthread_join waiter", *dining);
}



