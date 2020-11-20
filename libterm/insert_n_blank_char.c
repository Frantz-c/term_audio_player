/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   insert_n_blank_char.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:48:51 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:26:45 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_insert_n_blank_char(int n)
{
	static char			*insert = NULL;
	static char			*insert2 = NULL;
	static unsigned int len = 0;
	char				*command;

	if (!len)
	{
		if ((insert = tgetstr("IC", NULL)) == NULL)
		{
			if ((insert2 = tgetstr("ic", NULL)) == NULL)
				return ;
			len = strlen(insert2);
		}
		else
			len = 1;
	}
	if (insert)
	{
		command = tgoto(insert, 0, n);
		write(2, command, strlen(command));
	}
	else if (insert2)
		while (n--)
			write(2, insert2, len);
}
