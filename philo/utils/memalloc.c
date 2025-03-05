/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:44:48 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 11:50:58 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*memalloc(size_t size, t_ctx *ctx)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		errexit(FAIL, "malloc", &ctx);
	memset(mem, 0, size);
	if (!mem)
		errexit(FAIL, "memset", &ctx);
	return (mem);
}
