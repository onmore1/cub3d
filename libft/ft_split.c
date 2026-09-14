/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vananiev <vananiev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:39:49 by vananiev          #+#    #+#             */
/*   Updated: 2026/04/02 15:16:42 by vananiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>

static void	nuke_em_all(char **arr, int word_index)
{
	int	i;

	i = 0;
	while (i < word_index)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	word_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*word_alloc_copy(char const *s, int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	**fill_words(char const *s, char c, char **arr, int words)
{
	int	index;
	int	word_index;
	int	start;

	index = 0;
	word_index = 0;
	while (s[index] && word_index < words)
	{
		while (s[index] == c)
			index++;
		start = index;
		while (s[index] && s[index] != c)
			index++;
		arr[word_index] = word_alloc_copy(s, start, index - start);
		if (!arr[word_index])
			return (nuke_em_all(arr, word_index), NULL);
		word_index++;
	}
	arr[word_index] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	if (!s || !s[0] || s[0] == c)
		return (NULL);
	words = word_counter(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	return (fill_words(s, c, arr, words));
}
// int	main(void)
// {
// 	char	**res;
// 	int		i;

// 	res = ft_split("hello,,world, loorce,cwer,43424,111111,   ", ',');
// 	if (!res)
// 	{
// 		printf("Allocation failed.\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf("res[%d] = \"%s\"\n", i, res[i]);
// 		free(res[i]);
// 		i++;
// 	}
// 	free(res);
// 	return (0);
// }
