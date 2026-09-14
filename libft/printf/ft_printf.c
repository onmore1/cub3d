/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:54:37 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/21 16:23:40 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	type_finder(char c)
{
	int		index;
	char	*types;

	types = "cspdiuxX%";
	index = 0;
	while (types[index])
	{
		if (types[index] == c)
			return (c);
		index++;
	}
	return (0);
}

int	ptr_helper(va_list *ap)
{
	void	*ptr;
	int		printed;

	ptr = va_arg(*ap, void *);
	printed = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	printed += ft_putstr("0x");
	printed += hex_convert_ptr((uintptr_t)ptr);
	return (printed);
}

int	func_caller(char type, va_list *ap)
{
	if (type == 'c')
		return (ft_putchar(va_arg(*ap, int)));
	if (type == 's')
		return (ft_putstr(va_arg(*ap, char *)));
	if (type == 'p')
		return (ptr_helper(ap));
	if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(*ap, int)));
	if (type == 'u')
		return (ft_putnbr_unsigned(va_arg(*ap, unsigned int)));
	if (type == 'x')
		return (hex_convert_x(va_arg(*ap, unsigned int), 0));
	if (type == 'X')
		return (hex_convert_x(va_arg(*ap, unsigned int), 1));
	if (type == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		index;
	char	type;

	va_start(ap, format);
	count = 0;
	index = 0;
	while (format[index])
	{
		if (format[index] == '%' && format[index + 1])
		{
			type = type_finder(format[++index]);
			if (type)
				count += func_caller(type, &ap);
			else
				count += ft_putchar(format[index]);
		}
		else
			count += ft_putchar(format[index]);
		index++;
	}
	va_end(ap);
	return (count);
}
