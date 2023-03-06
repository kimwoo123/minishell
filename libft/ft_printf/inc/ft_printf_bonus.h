/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:20:58 by wooseoki          #+#    #+#             */
/*   Updated: 2022/12/08 19:33:41 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_items
{
	int		width;
	int		space;
	int		precision;
	int		minus;
	int		plus;
	int		zero;
	int		sharp;
	int		dot;
	int		len;
	char	specifier;
}	t_items;

int		ft_printf(const char *string, ...);
int		is_item(char c);
int		is_digit(char c);
int		is_specifier(char c);
int		ft_strlen(char *str);
int		ft_hexlen(unsigned long ptr);
int		ft_numlen(int num);
int		ft_unumlen(unsigned int num);
int		set_item(t_items *item_info, char c);
int		convert_c(int c, t_items *item_info);
int		convert_s(char *str, t_items *item_info);
int		convert_p(void *ptr, t_items *item_info);
int		convert_x(unsigned int num, t_items *item_info);
int		convert_u(unsigned int num, t_items *item_info);
int		convert_i(int num, t_items *item_info);
int		convert_specifier(t_items *item_info, va_list ap);
int		check_format(const char *string, va_list ap, int *totla_len);
int		print_string(va_list ap, const char *string);
char	check_sign(int num, t_items *item_info);
void	add_sign(t_items *item_info, int len, char sign);
void	putnbr(int num);
void	putunbr(unsigned int num);
void	putstr_len(char *str, int len);
void	puthex(unsigned int num, char *hex_base);
void	put_ulhex(unsigned long ptr, char *hex_base);
void	put_sharp(int sharp_flag, char specifier, unsigned int num);
void	putptr(unsigned long ptr);
void	init_iteminfo(t_items *item_info);
void	fill_width(int zero_flag, int len);
void	fill_precision(t_items *item_info);
void	print_u(unsigned int num, t_items *item_info);
void	print_x(unsigned int num, t_items *item_info, char *hex_base);
void	print_i(int num, t_items *item_info, char sign);
#endif
