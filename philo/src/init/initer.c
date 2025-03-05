/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:50:37 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_thread *philo, t_ctx *ctx, int i)
{
	philo->id = i + 1;
	philo->t_born = gettime();
	mxinit(&philo->leftlock, ctx);
	mxinit(&philo->rightlock, ctx);
	philo->ctx = ctx;
}

/**
 * @brief Initialize context of programm
 * 
 * @param ctx pointer to context
 * @param argv arguments
 * 
 */
void	init(t_ctx **ctx, char **argv)
{
	*ctx = (t_ctx *)memalloc(sizeof(t_ctx), NULL);
	(*ctx)->philos = (t_thread *)memalloc(sizeof(t_thread) * (*ctx)->n_ph, *ctx);
	(*ctx)->n_ph = ft_atoi(argv[1]);
	(*ctx)->t_die = ft_atoi(argv[2]);
	(*ctx)->t_eat = ft_atoi(argv[3]);
	(*ctx)->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*ctx)->meals = ft_atoi(argv[5]);
	else
		(*ctx)->meals = -1;
}
