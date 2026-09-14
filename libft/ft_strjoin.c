/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:20:35 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/07 14:08:34 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>
static int	length(const char*s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	index;
	char	*ptr;

	s1_len = length(s1);
	s2_len = length(s2);
	index = 0;
	ptr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ptr == NULL)
		return (NULL);
	while (index < s1_len)
	{
		ptr[index] = s1[index];
		index++;
	}
	index = 0;
	while (index < s2_len)
	{
		ptr[index + s1_len] = s2[index];
		index++;
	}
	ptr[s1_len + s2_len] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	char	s1[] = "hello ";
// 	char	s2[] = "add me";
// 	char	*result = ft_strjoin(s1, s2);
// 	printf("%s", result);
// 	return (0);
// }