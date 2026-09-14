/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:16:25 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 18:07:38 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//allocates a memomry for substr with 
//length of len and starting from start
//
//s_len - start < len checks how much we shoud allocate mem
//if the length goes after the end of the str
int	length(char const *s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	s_len;
	size_t	sub_len;
	char	*ptr;

	s_len = length(s);
	if (start >= s_len)
		sub_len = 0;
	else if (s_len - start < len)
		sub_len = s_len - start;
	else
		sub_len = len;
	ptr = malloc(sub_len + 1);
	if (!ptr)
		return (NULL);
	index = 0;
	while (index < sub_len && s[start + index])
	{
		ptr[index] = s[start + index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}
/* int	main(void)
{
	char	s[] = "Learning at Codam";
	unsigned int	start = 13;
	size_t	len = 5;
	char	*res = ft_substr(s, start, len);
	printf("%s\n", res);
	free(res);
	return (0);
} */