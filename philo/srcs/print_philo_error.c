/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfukushi <hfukushi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:25 by hfukushi          #+#    #+#             */
/*   Updated: 2023/10/25 12:44:11 by hfukushi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_return	print_philo_error(char *error_message, t_return return_val, const char *file, const char *func)
{
	printf("%s%s#[philo error]%s: %s   #file: %s   #func: %s\n",COLOR_RED, COLOR_BOLD,
		COLOR_RESET, error_message, file, func);
	return (return_val);
}

t_return	print_invalid_arg(t_return return_val, char * error_arg_message)
{
	printf("%s%s#[philo error]%s: invalid_argument #%s\n",COLOR_RED, COLOR_BOLD,
		COLOR_RESET, error_arg_message);
	return (return_val);
}
