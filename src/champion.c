/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:52:36 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/16 14:22:22 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** GLOBAL VARIABLE G_OP_TAB
** NEEDED ONLY FOR SUBSTRACT INFORMATION ABOUT OPERATIONS
*/

t_op g_op_tab[] = { {0, 0, 0, 0, 0, 0, 0},
	{"live", 1, {D}, 1, 10, 0, 0},
	{"live", 1, {D}, 1, 10, 0, 0},
	{"ld", 2, {DI, R}, 2, 5, 1, 0},
	{"st", 2, {R, RI}, 3, 5, 1, 0},
	{"add", 3, {R, R, R}, 4, 10, 1, 0},
	{"sub", 3, {R, R, R}, 5, 10, 1, 0},
	{"and", 3, {RDI, RDI, R}, 6, 6, 1, 0},
	{"or", 3, {RDI, RDI, R}, 7, 6, 1, 0},
	{"xor", 3, {RDI, RDI, R}, 8, 6, 1, 0},
	{"zjmp", 1, {D}, 9, 20, 0, 1},
	{"ldi", 3, {RDI, RD, R}, 10, 25, 1, 1},
	{"sti", 3, {R, RDI, RD}, 11, 25, 1, 1},
	{"fork", 1, {D}, 12, 800, 0, 1},
	{"lld", 2, {DI, R}, 13, 10, 1, 0},
	{"lldi", 3, {RDI, RD, R}, 14, 50, 1, 1},
	{"lfork", 1, {D}, 15, 1000, 0, 1},
	{"aff", 1, {R}, 16, 2, 1, 0} };

t_champ		*create_champ(void)
{
	t_champ	*champ;

	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	ft_bzero((void*)champ, sizeof(t_champ));
	return (champ);
}

void		free_champ(t_champ **champ)
{
	if (champ && *champ)
	{
		ft_strdel(&(*champ)->name);
		ft_strdel(&(*champ)->comment);
		del_instr(&(*champ)->instr);
		del_label(&(*champ)->labels);
		free(*champ);
		*champ = NULL;
	}
}
