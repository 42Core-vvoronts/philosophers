/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/14 19:49:09 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*memalloc(long size, void *ptr)
{
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

void	init_philo(t_philo *philo, t_ctx *ctx, int i)
{
	philo->id = i + 1;
	philo->ctx = ctx;
	philo->right_fork = &ctx->forks[i];
	if (ctx->n_philos == 1)
	{
		philo->left_fork = NULL;
		return ;
	}
	if (philo->id == ctx->n_philos)
		philo->left_fork = &ctx->forks[0];
	else if (philo->id == 1)
		philo->left_fork = &ctx->forks[ctx->n_philos - 1];
	else
		philo->left_fork = &ctx->forks[i + 1];
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

	ctx = (t_ctx *)memalloc(sizeof(t_ctx *), NULL);
	if (!ctx)
		return (FAIL);
	ctx->n_philos = ft_atoi(argv[1]);
	ctx->t_die = ft_atoi(argv[2]);
	ctx->t_eat = ft_atoi(argv[3]);
	ctx->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		ctx->n_meals = ft_atoi(argv[5]);
	ctx->uni_lock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), ctx);
	ctx->write_lock = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), ctx);
	ctx->forks = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t) * ctx->n_philos, ctx);
	if (!ctx->forks || !ctx->uni_lock || !ctx->write_lock)
	{
		ft_exit(FAIL, "malloc()", ctx);
		return (NULL); 
	}
	i = ctx->n_philos;
	while (i-- && ctx->f_error == false)
		mxinit(&ctx->forks[i], ctx);
	mxinit(ctx->uni_lock, ctx);
	mxinit(ctx->write_lock, ctx);
	ctx->philos = (t_philo *)memalloc(sizeof(t_philo) * ctx->n_philos, ctx);
	if (ctx->f_error == true)
		return (NULL);
	return (ctx);
}
