/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:05:51 by chajung           #+#    #+#             */
/*   Updated: 2022/12/10 16:12:04 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_data
{
	int	width;
	int	now_width;
	int	precision;
	int	now_precision;
	int	precision_dot;
	int	plus;
	int	minus;
	int	zero;
	int	space;
	int	hash;
}	t_data;

int	ft_printf(const char *format, ...);

/* specifier */
void	ft_print_c(char c, t_data *flag, int *count);
void	ft_print_s(char *str, t_data *flag, int *count);
void	ft_print_diu(long long nbr, t_data *flag, int *count);
void	ft_print_p(unsigned long nbr, t_data *flag, int *count);
void	ft_print_x(unsigned int nbr, t_data *flag, char format, int *count);

/* utils0 */
void	flag_init(t_data *flag);
void	ft_putnbr_diu(long long nbr, int *count);
void	ft_putnbr_addr(unsigned long nbr, int *count);
void	ft_putnbr_hex(unsigned int nbr, char format, int *count);

/* utils1 */
void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putpadding(char c, int repeat, int *count);
int		ft_nbrlen(long long nbr);
int		ft_hexlen(unsigned long nbr);

#endif
