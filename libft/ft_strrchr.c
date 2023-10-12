/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:44:28 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/11 23:08:56 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_char;

	while (*s != '\0')
	{
		if (*s == (char)c)
			last_char = s;
		s++;
	}
	return ((char *)last_char);
}

/* int	main(void) {
	const char str[] = "https://www.tutorialspoint.com";
	const char ch = 'p';
	char *ret;

	ret = ft_strrchr(str, ch);
	printf("String after %c is - %s\n", ch, ret);

	return 0;
}
 */
