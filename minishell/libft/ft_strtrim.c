/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalyout <fbalyout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:13:58 by fbalyout          #+#    #+#             */
/*   Updated: 2024/10/26 16:13:58 by fbalyout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char *set)
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

static int	count_charset(char *s1, char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = ft_strlen(s1);
	count = 0;
	while (is_charset(s1[i], set)) 
	{
		count++;
		i++;
	}
	if (s1[i] != '\0')
	{
		while (is_charset(s1[--j], set)) 
		{
			count++;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len_s1;
	int		charset_nb;
	char	*string;

	len_s1 = ft_strlen((char *)s1);
	charset_nb = count_charset((char *)s1, (char *)set);
	string = (char *)malloc((len_s1 - charset_nb + 1) * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (is_charset(s1[i], (char *)set)) 
		i++;
	while (is_charset(s1[len_s1 - 1], (char *)set)) 
		len_s1--;
	j = 0;
	while ((i <= (len_s1 - 1)))
		string[j++] = s1[i++];
	string[j] = '\0';
	return (string);
}
