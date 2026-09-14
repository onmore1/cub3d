/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:59:44 by vananiev          #+#    #+#             */
/*   Updated: 2025/05/08 18:29:17 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//1. chekcing where trimmed str starts from
//2.end now equals the start and we add it till we reach 
//null termintaor.
//3.while we keep landing on the substr we move back
//to trim this part.
//+2 in case if the whole str is set so the malloc will never be 0
//so end - start = - 1.End is not the same because we -- him(null)
static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = start;
	while (s1[end])
		end++;
	end--;
	while (end >= start && is_in_set(s1[end], set))
		end--;
	res = malloc(end - start + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}

/*
int	main(void)
{
	char	*s1 = "C123456ABC";
	char	*set = "ABC";
	char	*trim = ft_strtrim(s1, set);
	printf("%s\n", trim);
	free(trim);
	return (0);
}
*/
