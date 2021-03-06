/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wrappers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 18:40:53 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/27 22:04:24 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_setup(const char *format, t_result *result)
{
	ft_bzero(result, sizeof(t_result));
	result->format = format;
	result->lenght_format = ft_strlen(format);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_result	result;

	ft_bzero(&result, sizeof(result));
	pf_setup(format, &result);
	va_start(ap, format);
	pf_engine(&ap, &result);
	va_end(ap);
	write(1, result.print, result.length_print);
	ft_strdel(&result.print);
	return (result.length_print);
}

int			ft_sprintf(char *buf, const char *format, ...)
{
	va_list		ap;
	t_result	result;

	ft_bzero(&result, sizeof(result));
	pf_setup(format, &result);
	va_start(ap, format);
	pf_engine(&ap, &result);
	va_end(ap);
	ft_memcpy(buf, result.print, result.length_print);
	ft_strdel(&result.print);
	return (result.length_print);
}

int			ft_pprintf(char **buf, const char *format, ...)
{
	va_list		ap;
	t_result	result;

	ft_bzero(&result, sizeof(result));
	pf_setup(format, &result);
	va_start(ap, format);
	pf_engine(&ap, &result);
	va_end(ap);
	*buf = result.print;
	return (result.length_print);
}

int			ft_fdprintf(ssize_t fd, const char *format, ...)
{
	va_list		ap;
	t_result	result;

	ft_bzero(&result, sizeof(result));
	pf_setup(format, &result);
	va_start(ap, format);
	pf_engine(&ap, &result);
	va_end(ap);
	if (write(fd, result.print, result.length_print) == -1)
	{
		perror("ft_fdprintf: ");
		exit(EXIT_FAILURE);
	}
	ft_strdel(&result.print);
	return (result.length_print);
}
