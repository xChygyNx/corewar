/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utility.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:21:32 by astripeb          #+#    #+#             */
/*   Updated: 2019/11/14 18:09:23 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		del_one_instr(t_instr **instr)
{
	if (instr && *instr)
	{
		del_args(&(*instr)->args, (*instr)->num_args);
		(*instr)->prev = NULL;
		(*instr)->next = NULL;
		ft_memdel((void*)instr);
	}
}

t_instr			*new_instruct(t_op *op)
{
	t_instr		*instr;

	if (!(instr = (t_instr*)malloc(sizeof(t_instr))))
		return (NULL);
	ft_bzero((void*)instr, sizeof(t_instr));
	instr->code = op->code;
	instr->cycles2go = op->cycles2go;
	instr->num_args = op->num_args;
	instr->tdir_size = !op->tdir_size ? 4 : 2;
	if (!(instr->args = (t_arg*)malloc(sizeof(t_arg) * instr->num_args)))
	{
		ft_memdel((void*)&instr);
		return (NULL);
	}
	ft_bzero((void*)instr->args, sizeof(t_arg) * instr->num_args);
	instr->next = NULL;
	instr->prev = NULL;
	return (instr);
}

void			del_instr(t_instr **begin)
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

t_instr			*add_instr2end(t_instr *start, t_instr *instr)
{
	t_instr		*temp;

	if (!start)
	{
		start = instr;
		return (start);
	}
	temp = start;
	while (temp->next)
		temp = temp->next;
	temp->next = instr;
	instr->next->prev = instr;
	return (start);
}

void			print_instruct(t_instr *instr)
{
	ft_printf("___________________________ \n");
	ft_printf("| code | num_arg | offset |\n");
	while (instr)
	{
		ft_printf("| %4d | %7d | %6d |\n",\
		instr->code, instr->num_args, instr->offset);
		instr = instr->next;
	}
	ft_printf("|_________________________|\n");
}
