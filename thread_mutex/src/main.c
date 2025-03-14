/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:33:37 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 14:14:27 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Main function, program entry point
 * 
 * @param argc Number of arguments
 * @param argv Arguments
 * 
 * @return int
 */
int	main(int argc, char **argv)
{
	t_ctx	*ctx;

	validate(argv, argc);
	init(&ctx, argv);
	simulate(&ctx);
	destroy(&ctx);
	return (0);
}
