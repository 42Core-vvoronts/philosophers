/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 14:25:50 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sminit(sem_t *sem, unsigned int val, t_ctx *ctx)
{
	if (sem_init(sem, 0, val) != 0)
		return (ft_exit(FAIL, "sem_init()", ctx));
	return (SUCCESS);
}

int	smdestroy(sem_t *sem, t_ctx *ctx)
{
	if (sem_destroy(sem) != 0)
		return (ft_exit(FAIL, "sem_destroy()", ctx));
	return (SUCCESS);
}

int	smwait(sem_t *sem, t_ctx *ctx)
{
	if (sem_wait(sem) != 0)
		return (ft_exit(FAIL, "sem_wait()", ctx));
	return (SUCCESS);
}

int	smpost(sem_t *sem, t_ctx *ctx)
{
	if (sem_post(sem) != 0)
		return (ft_exit(FAIL, "sem_post()", ctx));
	return (SUCCESS);
}

int	smunlink(const char *name, t_ctx *ctx)
{
	if (sem_unlink(name) != 0)
		return (ft_exit(FAIL, "sem_unlink()", ctx));
	return (SUCCESS);
}
