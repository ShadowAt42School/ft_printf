/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghayev <maghayev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:06:21 by maghayev          #+#    #+#             */
/*   Updated: 2020/02/11 18:57:08 by maghayev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <inttypes.h>
# include "libft.h"

/*
**	Length
*/
# define NO	0
# define H	1
# define HH 2
# define L 	3
# define LL 4
# define J 	5
# define Z 	6
# define T 	7
# define LF	8
# define DSTR_MAX 50

/*
**	Varg
**	Union for all possible lengths(specifier agnostic)	**
*/
union				u_argument {
	char					schar;
	unsigned char			uchar;
	char					*str;
	short int				shint;
	int						intd;
	long int				lint;
	long long int			llint;
	unsigned int			uintd;
	unsigned short int		ushintd;
	unsigned long int		ulint;
	unsigned long long int	ullint;
	double					dnumber;
	long double				ldnumber;
	wchar_t					wchar;
	wchar_t					*wstr;
	size_t					sizet;
	intmax_t				intmax;
	uintmax_t				uintmax;
	void					*pspec;
	ptrdiff_t				ptrdiff;
};

/*
**	Structs
*/
typedef struct		s_string_decoration
{
	t_bool					is_ljustify;
	t_bool					is_force_sign;
	t_bool					is_blank_space;
	t_bool					is_preceed_ox;
	t_bool					is_force_decimal;
	t_bool					is_capital;
	t_bool					is_pad_zeros;
	t_bool					is_precision;

}					t_string_decoration;

typedef struct		s_integer_values
{
	long long int			llin;
	unsigned long long int	ullin;
	char					buffer[DSTR_MAX];
}					t_integer_values;

typedef struct		s_fmtlen
{
	int						aux;
	int						value;
	int						processed;
}					t_fmtlen;

typedef struct		s_formater
{
	unsigned char			flags;
	int						width;
	int						precision;
	unsigned short int		length;
	unsigned char			specifier;
	t_fmtlen				len;
	t_string_decoration		decorators;
	t_integer_values		intval;
	union u_argument		value;
}					t_formater;

typedef	struct		s_result
{
	const char				*format;
	char					*print;
	int						lenght_format;
	int						length_print;
}					t_result;

/*
**	Wrappers: ft_printf, ft_sprintf
*/
int					ft_printf(const char *format, ...);

/*
**	Engine
*/
void				ft_engine(va_list *ap, t_result *result);
t_list				*parse_format(va_list *ap, const char **format_origin);
t_list				*build_format(t_formater *formater);
void				finalize(t_result *result, t_list *pieces);

/*
**	Format Parsers
*/
void				parse_flags(
						const char **format, t_formater *formater, void *ap);
void				parse_width_precision(
						const char **format, t_formater *formater, va_list *ap);
void				parse_length(
						const char **format, t_formater *formater, void *ap);
void				parse_specifier(
						const char **format, t_formater *formater, va_list *ap);
void				build_decorators(t_formater *formater);

/*
**	Format Result Length
*/
void				prepare_length(
								unsigned int *current_length, t_formater *form);

/*
**	Format String Builders
*/
void				build_flags(
						char **res, t_formater *fmt, unsigned int str_start);
void				build_precision(
						char **res, t_formater *fmt, unsigned int str_start);
void				build_specifier(
						char **res, t_formater *fmt, unsigned int str_start);

/*
**	Helpers
*/

/*
**	Format checks
*/
t_bool				is_comp(char x);
t_bool				is_flag(char x);
t_bool				is_widpre(char x);
t_bool				is_len(char x);
t_bool				is_spec(char x);

/*
**	Specifier check
*/
t_bool				is_float(char x);
t_bool				is_int(char x);
t_bool				is_sint(char x);
t_bool				is_uint(char x);
t_bool				is_uints(char x);
t_bool				is_pointer(char x);
t_bool				is_strs(char x);
t_bool				is_str(char x);
t_bool				is_char(char x);

/*
**	Flag checks
*/
t_bool				is_fsp(unsigned char x);
t_bool				is_fsm(unsigned char x);
t_bool				is_fspc(unsigned char x);
t_bool				is_fhs(unsigned char x);
t_bool				is_fzero(unsigned char x);

/*
**	Base checks
*/
t_bool				is_base10(char x);
t_bool				is_basen10(char x);
int					base(char x);
int					basen10(char x);

/*
**	Aux
*/
int					flhslen(char x);
char				*flhsstr(char x);
char				*flhsstrx(char x);
t_bool				caplen(char x);

#endif
