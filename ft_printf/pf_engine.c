/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:02:29 by maghayev          #+#    #+#             */
/*   Updated: 2020/03/27 17:21:13 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_finalize(t_result *result, t_list *pieces)
{
	t_list			*pstart;
	t_list			*poped;
	unsigned int	cur_len;

	cur_len = 0;
	pstart = pieces;
	while (pstart)
	{
		result->length_print += pstart->content_size;
		pstart = pstart->next;
	}
	result->print = ft_strnew(result->length_print);
	pstart = pieces;
	while ((poped = pstart))
	{
		pstart = pstart->next;
		if (poped->content_size != 0)
		{
			ft_memcpy(result->print + cur_len,
										poped->content, poped->content_size);
			cur_len += poped->content_size;
		}
		ft_strdel((char**)(&poped->content));
		ft_memdel((void**)(&poped));
	}
}

void		pf_engine(va_list *ap, t_result *result)
{
	t_list	*pieces;
	char	*clean_str;
	int		clean_str_len;

	pieces = NULL;
	while (*result->format)
	{
		if (*result->format == '%')
		{
			result->format++;
			if (!*result->format)
				break ;
			ft_lstaddend(&pieces, pf_parse_format(ap, &result->format));
			continue;
		}
		clean_str_len = ft_strdelim(&clean_str, result->format, '%');
		ft_lstaddend(&pieces, ft_lstnewp(clean_str, clean_str_len));
		result->format += clean_str_len;
	}
	pf_finalize(result, pieces);
}

t_list		*pf_parse_format(va_list *ap, const char **format_origin)
{
	t_formater	formatter;

	ft_bzero(&formatter, sizeof(t_formater));
	while (!pf_is_spec(**format_origin) && pf_is_comp(**format_origin))
	{
		if (pf_is_flag(**format_origin))
			pf_parse_flags(format_origin, &formatter, ap);
		if (pf_is_widpre(**format_origin))
			pf_parse_width_precision(format_origin, &formatter, ap);
		if (pf_is_len(**format_origin))
			pf_parse_length(format_origin, &formatter, ap);
	}
	pf_parse_specifier(format_origin, &formatter, ap);
	pf_build_decorators(&formatter);
	return (pf_build_format(&formatter));
}

t_list		*pf_build_format(t_formater *fmt)
{
	char			*result;
	unsigned int	total_length;

	total_length = 0;
	if (fmt->specifier)
	{
		pf_prepare_length(&total_length, fmt);
		result = ft_strnew(total_length);
		if (fmt->width > 0)
			ft_memset(result, fmt->decorators.is_pad_zeros &&
					!fmt->decorators.is_precision ? '0' : ' ', total_length);
		if (fmt->decorators.is_precision)
			pf_build_precision(&result, fmt, fmt->decorators.is_ljustify
						? fmt->len.aux : total_length - fmt->len.processed);
		pf_build_specifier(&result, fmt, fmt->decorators.is_ljustify ?
					(fmt->len.processed - fmt->len.value + fmt->len.aux) :
												total_length - fmt->len.value);
		pf_build_flags(&result, fmt, fmt->decorators.is_ljustify ? 0
						: total_length - fmt->len.processed - fmt->len.aux);
	}
	return (ft_lstnewp(result, total_length));
}
