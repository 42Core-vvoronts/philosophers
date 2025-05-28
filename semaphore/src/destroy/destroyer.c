/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 18:50:19 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_ctx *ctx)
{
	if (!ctx)
		return ;
	smclose(ctx->forks);
	smclose(ctx->semwri);
	smclose(ctx->semful);
	smclose(ctx->semdie);
	smclose(ctx->semgo);
	smunlink(SEMFUL);
	smunlink(SEMWRI);
	smunlink(SEMDIE);
	smunlink(SEMFORK);
	smunlink(SEMGO);
	if (ctx->philos)
		free(ctx->philos);
	if (ctx->observer)
		free(ctx->observer);
	free(ctx);
}
