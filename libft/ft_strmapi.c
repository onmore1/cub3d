/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:29:13 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 18:35:43 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//creates new str and applying function for
//each char of the freshly created str
static int	length(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	index;
	int				s_len;

	if (!s || !f)
		return (NULL);
	s_len = length(s);
	ptr = malloc((s_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	index = 0;
	while (s[index])
	{
		ptr[index] = f(index, s[index]);
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

/*
char	f(unsigned int i, char c)
{
	if (!(i % 2) && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int	main(void)
{
	char	*s = "libftisawesome";
	char	*result;

	result = ft_strmapi(s, f);
	if (!result)
		return (1);
	printf("Original: %s\n", s);
	printf("Mapped  : %s\n", result);
	free(result);
	return (0);
}*/