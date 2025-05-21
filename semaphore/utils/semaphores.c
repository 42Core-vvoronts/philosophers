/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/21 17:42:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wrapper for sem_open()
 * 
 * @param name name of semaphore
 * @param value 
 * @param ctx context of program
 * 
 * @return int
 */
sem_t *smopen(const char *name, unsigned int value, t_ctx *ctx) 
{
	sem_t	*sem;

	sem	= sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED) 
	{
		ft_exit(FAIL, "sem_open", ctx);
		return (NULL);
	}
	sem_unlink(name);
	return (sem);
}

// Wrapper for sem_close()
int	smclose(sem_t *sem, t_ctx *ctx)
{
	if (sem_close(sem) != 0)
		return (ft_exit(FAIL, "sem_close", ctx));
	return (SUCCESS);
}

// Your existing wrappers
int	smwait(sem_t *sem, t_ctx *ctx)
{
	if (sem_wait(sem) != 0)
		return (ft_exit(FAIL, "sem_wait", ctx));
	return (SUCCESS);
}

int	smpost(sem_t *sem, t_ctx *ctx)
{
	if (sem_post(sem) != 0)
		return (ft_exit(FAIL, "sem_post", ctx));
	return (SUCCESS);
}

int	smunlink(const char *name, t_ctx *ctx)
{
	if (sem_unlink(name) != 0)
		return (ft_exit(FAIL, "sem_unlink", ctx));
	return (SUCCESS);
}
