/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 17:51:44 by vvoronts         ###   ########.fr       */
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
sem_t	*smopen(const char *name, unsigned int value, t_ctx *ctx)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
	{
		destroy(ctx);
		ft_exit(FAIL, "sem_open");
	}
	sem_unlink(name);
	return (sem);
}

// Your existing wrappers
void	smwait(sem_t *sem, t_ctx *ctx)
{
	if (sem_wait(sem) != 0)
	{
		destroy(ctx);
		ft_exit(FAIL, "sem_wait");
	}
}

void	smpost(sem_t *sem, t_ctx *ctx)
{
	if (sem_post(sem) != 0)
	{
		destroy(ctx);
		ft_exit(FAIL, "sem_post");
	}
}

// Wrapper for sem_close()
void	smclose(sem_t *sem)
{
	if (sem_close(sem) != 0)
	{
		ft_exit(FAIL, "sem_close");
	}
}

void	smunlink(const char *name)
{
	if (sem_unlink(name) != 0 && errno != ENOENT)
	{
		ft_exit(FAIL, "sem_unlink");
	}
}
