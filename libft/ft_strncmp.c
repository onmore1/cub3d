/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:11:06 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 18:34:01 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
// #include <string.h>
//retruns a s1 and s2 char differnce
//if the chars are not the same
//0 cause they are the same
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*pointer1;
	unsigned char	*pointer2;

	pointer1 = (unsigned char *)s1;
	pointer2 = (unsigned char *)s2;
	index = 0;
	while (index < n && (pointer1[index] || pointer2[index]))
	{
		if (pointer1[index] != pointer2[index])
			return ((int)(pointer1[index] - pointer2[index]));
		index++;
	}
	return (0);
}

/*
int main()
{
    char str[] = "ABCDEFG";
    char str2[] = "ABCCEFG";
    size_t number = 5;
    int result = ft_strncmp(str, str2, number);
    printf("%d", result);
    return (0);
}
*/
