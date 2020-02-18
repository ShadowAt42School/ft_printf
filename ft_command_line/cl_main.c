/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:36:19 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/17 20:32:44 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_command_line.h"

void	cl_init(char **args, t_option *options, size_t size)
{
	cl_set_opts(options, size);
	cl_engine(args);
}
