/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: fcordon <mhouppin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 16:35:21 by fcordon      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/11 14:45:00 by fcordon     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libterm.h"

#include <stdlib.h>

int		lt_init(void)
{
	const char	*term = getenv("TERM");

	if (term == NULL)
		return (-2);
	return (tgetent(NULL, term));
}
