/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:20:15 by chajung           #+#    #+#             */
/*   Updated: 2022/11/12 14:28:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ex_dstsize;

	ex_dstsize = ft_strlen(dst);
	if (ex_dstsize + 1 < dstsize)
	{
		i = 0;
		while (src[i] && ex_dstsize + i + 1 < dstsize)
		{
			dst[ex_dstsize + i] = src[i];
			i++;
		}
		dst[ex_dstsize + i] = '\0';
	}
	if (ex_dstsize < dstsize)
		return (ft_strlen(src) + ex_dstsize);
	else
		return (ft_strlen(src) + dstsize);
}
