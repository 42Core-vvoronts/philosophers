/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 15:19:58 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_program_input(t_ctx *ctx, char **argv)
{
	ctx->n_philos = ft_atol(argv[1]);
	ctx->t_die = ft_atol(argv[2]);
	ctx->t_eat = ft_atol(argv[3]);
	ctx->t_sleep = ft_atol(argv[4]);
	if (argv[5])
		ctx->n_meals = ft_atol(argv[5]);
}

void	alloc_semaphores(t_ctx *ctx)
{
	ctx->semdie = smopen(SEMDIE, 1, ctx);
	ctx->semful = smopen(SEMFUL, 1, ctx);
	ctx->semuni = smopen(SEMUNI, 1, ctx);
	ctx->semwri = smopen(SEMWRI, 1, ctx);
	ctx->forks = smopen(SEMFORK, ctx->n_philos, ctx);
	ctx->go = smopen(SEMGO, 0, ctx);
}

void	*memalloc(size_t size, void *ctx)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_exit(FAIL, "malloc", ctx);
	memset(ptr, 0, size);
	return (ptr);
}

/**
 * @brief Initialize each philo
 * 
 * @param ctx pointer to context
 * @param i philo index
 * 
 * printf("	%d: %ld\n", philo->id, philo->t_think);
 */
void	init_philo(t_ctx *ctx, int i)
{
	t_philo	*philo;

	philo = &ctx->philos[i];
	philo->id = i + 1;
	philo->ctx = ctx;
	if (ctx->n_philos % 2 == 0 && ctx->t_eat > ctx->t_sleep)
		philo->t_think = ctx->t_eat - ctx->t_sleep;
	else if (ctx->n_philos % 2 == 1 && ctx->t_eat == ctx->t_sleep)
		philo->t_think = ctx->t_eat;
	else if (ctx->n_philos % 2 == 1 && ctx->t_eat > ctx->t_sleep)
		philo->t_think = ctx->t_eat + (ctx->t_eat - ctx->t_sleep);
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
	save_program_input(ctx, argv);
	alloc_semaphores(ctx);
	ctx->observer = (pthread_t *)memalloc(sizeof(pthread_t), ctx);
	ctx->philos = (t_philo *)memalloc(sizeof(t_philo) * ctx->n_philos, ctx);
	i = 0;
	while (i < ctx->n_philos)
		init_philo(ctx, i++);
	return (ctx);
}
