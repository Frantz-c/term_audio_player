/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delete_current_line.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <fcordon@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 13:56:22 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:23:54 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_delete_current_line(void)
{
	static char			*delete = NULL;
	static unsigned int	len;

	if (!delete)
	{
		if ((delete = tgetstr("dl", NULL)) == NULL)
			return ;
		len = strlen(delete);
	}
	write(2, delete, len);
}
