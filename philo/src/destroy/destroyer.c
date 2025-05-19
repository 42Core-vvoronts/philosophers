/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/19 18:02:10 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    destroy(t_ctx *ctx)
{
    int  i;

    if (!ctx)
        return ;

    if (ctx->forks)
    {
        i = 0;
        while (i < ctx->n_philos)
        {
            mxdestroy(&ctx->forks[i], ctx);
            i++;
        }
        free(ctx->forks);
        ctx->forks = NULL;
    }

    if (ctx->die_lock)
    {
        mxdestroy(ctx->die_lock, ctx);
        free(ctx->die_lock);
        ctx->die_lock = NULL;
    }

    if (ctx->uni_lock)
    {
        mxdestroy(ctx->uni_lock, ctx);
        free(ctx->uni_lock);
        ctx->uni_lock = NULL;
    }

    if (ctx->write_lock)
    {
        mxdestroy(ctx->write_lock, ctx);
        free(ctx->write_lock);
        ctx->write_lock = NULL;
    }


    if (ctx->philos)
    {
        free(ctx->philos);
        ctx->philos = NULL;
    }

    free(ctx);
}