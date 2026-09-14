/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:12:06 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/20 16:48:10 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(const char *str);
int		hex_convert_x(unsigned int n, int is_upper);
int		hex_convert_ptr(uintptr_t n);
int		ft_putnbr(int n);
int		ft_putnbr_unsigned(unsigned int n);
int		ptr_helper(va_list *ap);

#endif