/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:58:25 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/12 10:48:12 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*sub;

	if (!s)
		return (NULL);
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	j = 0;
	if (!(sub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			while (s[i] && j < len)
				sub[j++] = s[i++];
			sub[j] = '\0';
			return (sub);
		}
		i++;
	}
	return (NULL);
}
