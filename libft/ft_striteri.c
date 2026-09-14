/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:09:46 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 12:22:08 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	f(unsigned int index, char *c)
// {
// 	if (index % 2 == 0)
// 		*c = '0';
// }

/* int	main(void) */
/* { */
/*	char	str[] = "11111111"; */
/*	ft_striteri(str, f); */
/*	printf("%s\n", str); */
/*	return (0); */
/* } */
