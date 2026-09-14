/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:39:46 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/20 16:42:12 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_convert_x(unsigned int n, int is_upper)
{
	char	*hex_map;
	int		printed;

	printed = 0;
	if (is_upper)
		hex_map = "0123456789ABCDEF";
	else
		hex_map = "0123456789abcdef";
	if (n >= 16)
		printed += hex_convert_x(n / 16, is_upper);
	ft_putchar(hex_map[n % 16]);
	printed++;
	return (printed);
}

int	hex_convert_ptr(uintptr_t n)
{
	char	*hex_map;
	int		printed;

	printed = 0;
	hex_map = "0123456789abcdef";
	if (n >= 16)
		printed += hex_convert_ptr(n / 16);
	ft_putchar(hex_map[n % 16]);
	printed++;
	return (printed);
}
