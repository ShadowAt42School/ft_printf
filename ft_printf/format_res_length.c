/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_res_length.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:45:54 by maghayev          #+#    #+#             */
/*   Updated: 2019/10/08 23:27:51 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_stdio.h"
#include <stdio.h>

static unsigned int			specifier_conv_length(t_formater *fmt)
{
	if (fmt->decorators.is_precision && fmt->precision == 0)
		if (fmt->integer_values.llin == 0 && fmt->integer_values.llin == 0)
			return (0);
	if (SIGNPOSSIBLE(fmt->specifier))
		return (ft_itoa_base((char*)fmt->integer_values.buffer,
			&fmt->integer_values.llin,
			BASE(fmt->specifier),
			SIGNPOSSIBLE(fmt->specifier)));
	else
		return (ft_itoa_base((char*)fmt->integer_values.buffer,
			&fmt->integer_values.ullin,
			BASE(fmt->specifier),
			SIGNPOSSIBLE(fmt->specifier)));
}

static unsigned int			numspecifier_length(t_formater *fmt)
{
	long long int			llin;
	unsigned long long int	ullin;

	if (fmt->length == HH && (ullin = ULLINTD(fmt->value.uchar)))
		llin = LLINTD(fmt->value.schar);
	else if (fmt->length == H && (ullin = ULLINTD(fmt->value.ushintd)))
		llin = LLINTD(fmt->value.shint);
	else if (fmt->length == L && (ullin = ULLINTD(fmt->value.ulint)))
		llin = LLINTD(fmt->value.lint);
	else if (fmt->length == LL && (ullin = ULLINTD(fmt->value.ullint)))
		llin = LLINTD(fmt->value.llint);
	else if (fmt->length == J && (ullin = ULLINTD(fmt->value.intmax)))
		llin = LLINTD(fmt->value.intmax);
	else if (fmt->length == Z && (ullin = ULLINTD(fmt->value.sizet)))
		llin = LLINTD(fmt->value.sizet);
	else if (fmt->length == T && (ullin = ULLINTD(fmt->value.intd)))
		llin = LLINTD(fmt->value.ptrdiff);
	else
	{
		ullin = ULLINTD(fmt->value.uintd);
		llin = LLINTD(fmt->value.intd);
	}
	fmt->integer_values.llin = llin;
	fmt->integer_values.ullin = ullin;
	return (specifier_conv_length(fmt));
}

static void					flags_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	unsigned int length;

	length = 0;
	if ((fmt->decorators.is_blank_space || fmt->decorators.is_force_sign ||
				fmt->integer_values.llin < 0) && SIGNPOSSIBLE(fmt->specifier)
													&& (fmt->aux_length += 1))
		length += 1;
	if (fmt->decorators.is_preceed_ox && fmt->integer_values.ullin != 0 &&
									(fmt->aux_length += LEN_OX(fmt->specifier)))
		length += fmt->aux_length;
	if ((fmt->decorators.is_precision && fmt->precision > fmt->width) ||
																	length > 0)
		*current_length += length;
}

/*
**	TODO: Add float length function
*/

static void					length_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	unsigned int	length;

	length = fmt->value_length;
	if (INT_SPEC(fmt->specifier))
	{
		if (fmt->decorators.is_precision)
			length = length < fmt->precision ? fmt->precision : length;
		else if (fmt->width > 0 && fmt->decorators.is_pad_zeros &&
					!fmt->decorators.is_left_justify && length < fmt->width)
			length = fmt->width - fmt->aux_length;
	}
	else if (fmt->specifier == 's')
		length = fmt->decorators.is_precision ? fmt->precision :
													ft_strlen(fmt->value.str);
	else
		length = 1;
	fmt->value_length = length == 1 ? 1 : fmt->value_length;
	fmt->processed_length = length;
	*current_length += length;
}

void						prepare_length(
	unsigned int *current_length,
	t_formater *fmt
)
{
	fmt->value_length = numspecifier_length(fmt);
	flags_length(current_length, fmt);
	length_length(current_length, fmt);
	if (fmt->width > 0 && fmt->width > *current_length)
		*current_length = fmt->width;
}