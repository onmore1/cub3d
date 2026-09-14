/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:26:27 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 18:32:12 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
//1.if the little is empty return a whole sring
//returns a pointer to a start of a little
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	index2;

	index = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[index] != '\0' && index < len)
	{
		index2 = 0;
		while (big[index + index2] == little[index2]
			&& (index + index2) < len)
		{
			if (little[index2 + 1] == '\0')
			{
				return ((char *)&big[index]);
			}
			index2++;
		}
		index++;
	}
	return (NULL);
}

/* 
int main()
{
    char big[] = "The name is Codam";
    char little[] = "name";
    size_t len = 17;
    char *result = ft_strnstr(big, little, len);
    printf("%s", result);
    return (0); 
}
*/
