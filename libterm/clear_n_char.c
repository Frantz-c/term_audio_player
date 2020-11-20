/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clear_n_char.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 17:30:28 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:23:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_clear_n_char(int n)
{
	static char	*clear;
	char		*command;

	if (!clear)
	{
		if ((clear = tgetstr("ec", NULL)) == NULL)
			return ;
	}
	command = tgoto(clear, 0, n);
	write(2, command, strlen(command));
}
