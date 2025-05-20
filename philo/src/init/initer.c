/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/20 15:04:00 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*memalloc(size_t size, void *ctx)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		if (ctx)
			((t_ctx *)ctx)->f_error = true;
		return (NULL);
	}
	memset(ptr, 0, size);
	return (ptr);
}

void	init_philo(t_ctx *ctx, int i)
{
	t_philo	*philo;

	philo = &ctx->philos[i];
	philo->id = i + 1;
	philo->ctx = ctx;
	philo->right_fork = &ctx->forks[i];
	if (ctx->n_philos == 1)
	{
		philo->left_fork = NULL;
		return ;
	}
	philo->left_fork = &ctx->forks[(i + 1) % ctx->n_philos];
	if (ctx->n_philos % 2 == 0 && ctx->t_eat > ctx->t_sleep)
		philo->t_think = ctx->t_eat - ctx->t_sleep;
	else if (ctx->n_philos % 2 == 1)
	{
		philo->t_think = ctx->t_eat;
		if (ctx->t_eat > ctx->t_sleep)
			philo->t_think += ctx->t_eat - ctx->t_sleep;
	}
	else
		philo->t_think = 0;
}

/**
 * @brief Initialize context of programm
 * 
 * @param ctx pointer to context
 * @param argv arguments
 * 
 */
t_ctx	*init(char **argv)
{
	int		i;
	t_ctx	*ctx;

	ctx = (t_ctx *)memalloc(sizeof(t_ctx), NULL);
	if (!ctx)
		return (NULL);
	ctx->n_philos = ft_atol(argv[1]);
	ctx->t_die = ft_atol(argv[2]);
	ctx->t_eat = ft_atol(argv[3]);
	ctx->t_sleep = ft_atol(argv[4]);
	if (ctx->n_philos % 2 == 1 && ctx->t_eat > ctx->t_sleep)
		ctx->t_think = ctx->t_eat - ctx->t_sleep;
	if (argv[5])
		ctx->n_meals = ft_atol(argv[5]);
	ctx->die_lock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), ctx);
	ctx->uni_lock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), ctx);
	ctx->write_lock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), ctx);
	ctx->forks = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t) * ctx->n_philos, ctx);
	if (!ctx->forks || !ctx->uni_lock || !ctx->write_lock)
	{
		ft_exit(FAIL, "malloc()", ctx);
		return (NULL); 
	}
	i = 0;
	while (i < ctx->n_philos && ctx->f_error == false)
		mxinit(&ctx->forks[i++], ctx);
	mxinit(ctx->die_lock, ctx);
	mxinit(ctx->uni_lock, ctx);
	mxinit(ctx->write_lock, ctx);
	ctx->philos = (t_philo *)memalloc(sizeof(t_philo) * ctx->n_philos, ctx);
	i = 0;
	while (i < ctx->n_philos && ctx->f_error == false)
		init_philo(ctx, i++);
	if (ctx->f_error == true)
		return (NULL);
	return (ctx);
}
