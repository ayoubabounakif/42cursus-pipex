/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 20:40:50 by aabounak          #+#    #+#             */
/*   Updated: 2021/05/23 20:41:00 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
