/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_delete.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/22 14:33:30 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:27:04 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_insert_n_lines_before(int n)
{
	static char	*insert = NULL;
	char		*command;

	if (!insert)
	{
		if ((insert = tgetstr("AL", NULL)) == NULL)
			return ;
	}
	command = tgoto(insert, 0, n);
	write(2, command, strlen(command));
}
