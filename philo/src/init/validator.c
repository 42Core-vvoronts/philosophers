/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:46:13 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/12 14:58:16 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Validate arguments
 * @param argv Arguments
 * @param argc Number of arguments
 * 
 * Validate number of arguments and their values
 */
int	validate(char **argv, int argc)
{
	char	*msg;

	msg = NULL;
	if (argc != 5 && argc != 6)
		msg = "Invalid number of arguments";
	else if (ft_atoi(argv[1]) > MAXPH || ft_atoi(argv[1]) <= 0)
		msg = "Invalid philosophers number";
	else if (ft_atoi(argv[2]) <= 0)
		msg = "Invalid time to die";
	else if (ft_atoi(argv[3]) <= 0)
		msg = "Invalid time to eat";
	else if (ft_atoi(argv[4]) <= 0)
		msg = "Invalid time to sleep";
	else if (argv[5] && (ft_atoi(argv[5]) <= 0))
		msg = "Invalid number of times each philosopher must eat";
	if (!msg)
		return (SUCCESS);
	writestd(msg, 2);
	return (FAIL);
}
