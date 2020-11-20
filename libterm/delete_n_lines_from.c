/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_n_lines_after.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:58:18 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:22:14 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_delete_n_lines_from(int n)
{
	static char	*delete = NULL;
	char		*command;

	if (!delete)
	{
		if ((delete = tgetstr("DL", NULL)) == NULL)
			return ;
	}
	command = tgoto(delete, 0, n);
	write(2, command, strlen(command));
}
