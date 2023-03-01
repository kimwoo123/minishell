/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:52:12 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 17:16:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dst_;
	const char	*src_;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst_ = (char *)dst;
	src_ = (const char *)src;
	if (dst_ < src_)
	{
		while (i++ < len)
			*dst_++ = *src_++;
	}
	else
	{
		dst_ += len;
		src_ += len;
		while (i++ < len)
			*--dst_ = *--src_;
	}
	return (dst);
}
