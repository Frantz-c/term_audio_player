/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_right.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:07:08 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:28:46 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_right(void)
{
	static char			*move = NULL;
	static unsigned int	len;

	if (!move)
	{
		if ((move = tgetstr("nd", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_right(int n)
{
	static char	*move = NULL;
	char		*command;

	if (!move)
	{
		if ((move = tgetstr("RI", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}
