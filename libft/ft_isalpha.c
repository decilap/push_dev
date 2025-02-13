/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecilap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:02:59 by ddecilap          #+#    #+#             */
/*   Updated: 2024/11/09 15:16:18 by ddecilap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int dec)
{
	if ((dec >= 'a' && dec <= 'z') || (dec >= 'A' && dec <= 'Z'))
		return (1);
	return (0);
}
