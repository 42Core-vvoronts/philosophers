/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:41:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/27 19:32:11 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(pthread_t *t, void *(*f)(void *), void *arg, t_ctx *ctx)
{
	int		code;

	code = pthread_create(t, NULL, f, arg);
	if (code != SUCCESS)
		ft_exit(FAIL, "pthread_create", ctx);
}

void	join_thread(pthread_t *thread, t_ctx *ctx)
{
	int		code;

	code = pthread_join(*thread, NULL);
	if (code != SUCCESS)
		ft_exit(code, "pthread_join", ctx);
}
