/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:24:20 by vminomiy          #+#    #+#             */
/*   Updated: 2020/03/09 16:03:33 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		main(int argc, char **argv)
{
	int		i;
	int		j;
	int		s[256];

	if (argc == 3)
	{
		i = 1;
		*s = 0;
		while (i < 3)
		{
			j = 0;
			while (argv[i][j])
			{
				if (!s[(unsigned char)argv[i][j]])
				{
					s[(unsigned char)argv[i][j]] = 1;
					write(1, &argv[i][j], 1);
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
