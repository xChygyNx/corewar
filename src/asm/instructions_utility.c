/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utility.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:21:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 17:36:50 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	del_args(t_arg **args, int num_args)
{
	int i;

	if (args && *args)
	{
		i = 0;
		while (i < num_args)
		{
			ft_memdel((void*)&(*args)[i].str);
			++i;
		}
		ft_memdel((void*)args);
	}
}

void		del_one_instr(t_instr **instr)
{
	if (instr && *instr)
	{
		del_args(&(*instr)->args, (*instr)->num_args);
		(*instr)->next = NULL;
		ft_memdel((void*)instr);
	}
}

t_instr		*new_instruct(t_op op)
{
	t_instr		*instr;

	if (!(instr = (t_instr*)malloc(sizeof(t_instr))))
		return (NULL);
	ft_bzero((void*)instr, sizeof(t_instr));
	instr->code = op.code;
	instr->code_args = op.code_args;
	instr->cycles2go = op.cycles2go;
	instr->num_args = op.num_args;
	instr->tdir_size = op.tdir_size;
	if (!(instr->args = (t_arg*)malloc(sizeof(t_arg) * instr->num_args)))
	{
		ft_memdel((void*)&instr);
		return (NULL);
	}
	ft_bzero((void*)instr->args, sizeof(t_arg) * instr->num_args);
	return (instr);
}

void		del_instr(t_instr **begin)
{
	t_instr		*temp;
	t_instr		*instr;

	if (begin && *begin)
	{
		instr = *begin;
		while (instr)
		{
			temp = instr;
			instr = instr->next;
			del_one_instr(&temp);
		}
		*begin = NULL;
	}
}

void		add_instr2end(t_instr **begin, t_instr *instr)
{
	t_instr		*temp;

	if (begin)
	{
		if (!*begin)
			*begin = instr;
		else
		{
			temp = *begin;
			while (temp->next)
				temp = temp->next;
			temp->next = instr;
		}
	}
}
