/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:31:07 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/20 16:41:27 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

int	ft_putnbr(int n)
{
	int	printed;

	printed = 0;
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		printed += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		printed += ft_putnbr(n / 10);
	printed += ft_putchar(n % 10 + '0');
	return (printed);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	printed;

	printed = 0;
	if (n >= 10)
		printed += ft_putnbr_unsigned(n / 10);
	printed += ft_putchar(n % 10 + '0');
	return (printed);
}
