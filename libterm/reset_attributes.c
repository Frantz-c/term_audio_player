/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reset_attributes.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 14:33:07 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:29:29 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"


void	lt_reset_attr(void)
{
	static const char	*reset = NULL;
	static unsigned int	len;

	if (!reset)
	{
		if ((reset = tgetstr("me", NULL)) == NULL)
			return ;
		len = strlen(reset);
	}
	write(2, reset, len);
}
