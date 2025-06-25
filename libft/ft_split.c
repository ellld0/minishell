/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavi-al <sdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:24:46 by sdavi-al          #+#    #+#             */
/*   Updated: 2025/01/20 09:07:16 by sdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char *s, char delim)
{
	int	count;
	int	in_str;

	count = 0;
	in_str = 0;
	while (*s)
	{
		if (*s != delim && !in_str)
		{
			in_str = 1;
			count++;
		}
		else if (*s == delim)
			in_str = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char *s, char delim)
{
	char	**result;
	int		i;
	char	*start;
	int		total_strs;

	i = 0;
	start = 0;
	total_strs = str_count(s, delim);
	result = (char **)malloc(sizeof(char *) * (total_strs + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s != delim)
		{
			start = s;
			while (*s && *s != delim)
				s++;
			result[i++] = ft_substr(start, 0, s - start);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

// char *ft_strncpy(char *s1, char *s2, int n)
// {
// 	int i = -1;

// 	while (++i < n && s2[i])
// 		s1[i] = s2[i];
// 	s1[i] = '\0';
// 	return (s1);
// }

// char	**ft_split(char *str)
// {
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;
// 	int wc = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
// 			i++;
// 		if (str[i])
// 			wc++;
// 		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
// 			i++;
// 	}
// 	char **out = (char **)malloc(sizeof(char *) * (wc + 1));
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
// 			i++;
// 		j = i;
// 		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
// 			i++;
// 		if (i > j)
// 		{
// 			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
// 			ft_strncpy(out[k++], &str[j], i - j);
// 		}
// 	}
// 	out[k] = NULL;
// 	return (out);
// }