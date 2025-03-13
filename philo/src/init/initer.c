/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/13 10:36:26 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_thread *philo, t_ctx *ctx, int i)
{
	philo->id = i + 1;
	philo->t_meal = gettime();
	philo->left = &ctx->forks[(i + 1) % ctx->n_ph];
	philo->right = &ctx->forks[i];
	// if (i == 0)
	// 	philo->left = &ctx->forks[ctx->n_ph - 1];
	// else
	// 	philo->left = &ctx->forks[i - 1];
	// if (i == ctx->n_ph - 1)
	// 	philo->right = &ctx->forks[0];
	// else
	// 	philo->right = &ctx->forks[i];
	mxinit(philo->left, ctx);
	mxinit(philo->right, ctx);
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
	int	i;

	*ctx = (t_ctx *)memalloc(sizeof(t_ctx), NULL);
	(*ctx)->n_ph = ft_atoi(argv[1]);
	(*ctx)->philos = (t_thread *)memalloc(sizeof(t_thread) * (*ctx)->n_ph, *ctx);
	(*ctx)->forks = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t) * (*ctx)->n_ph, *ctx);
	i = (*ctx)->n_ph;
	while (i--)
		mxinit(&(*ctx)->forks[i], *ctx);
	(*ctx)->meallock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), *ctx);
	(*ctx)->t_die = ft_atoi(argv[2]);
	(*ctx)->t_eat = ft_atoi(argv[3]);
	(*ctx)->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*ctx)->meals = ft_atoi(argv[5]);
	else
		(*ctx)->meals = -1;
}
