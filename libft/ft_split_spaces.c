/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnascime <mnascime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:38:50 by mnascime          #+#    #+#             */
/*   Updated: 2023/10/28 13:19:56 by mnascime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	beg_trim(const char *s, int i)
{
	while (s[i] != '\0' && !ft_isspace(s[i]))
		i++;
	return (i);
}

static char	*strs(const char *s, int i, int f)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char *) * (f - i));
	if (!str)
		return (NULL);
	while (s[i] && i < f)
	{
		str[j] = s[i++];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int	count_c(const char *s)
{
	size_t	f;

	f = 0;
	while (*s)
	{
		while (*s && !ft_isspace(*s))
			s++;
		if (*s && ft_isspace(*s))
			f++;
		while (*s && ft_isspace(*s))
			s++;
	}
	return (f);
}

char	**ft_split_spaces(char const *s)
{
	size_t	i;
	size_t	j;
	char	**ptrs;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	ptrs = malloc(sizeof(char *) * (ft_strlen(s) + count_c(s) + 1));
	if (!ptrs)
		return (NULL);
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		ptrs[j++] = strs(s, i, beg_trim(s, i));
		i = beg_trim(s, i);
	}
	ptrs[j] = 0;
	return (ptrs);
}
