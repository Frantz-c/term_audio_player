/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_up.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:09:31 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:29:07 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_move_up(void)
{
	static char			*move = NULL;
	static unsigned int	len = 0;

	if (!move)
	{
		if ((move = tgetstr("up", NULL)) == NULL)
			return ;
		len = strlen(move);
	}
	write(2, move, len);
}

void	lt_move_n_up(int n)
{
	static char			*move = NULL;
	char				*command;

	if (!move)
	{
		if ((move = tgetstr("UP", NULL)) == NULL)
			return ;
	}
	command = tgoto(move, 0, n);
	write(2, command, strlen(command));
}
