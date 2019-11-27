/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:13:31 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/27 20:40:32 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	int			i;
	t_options	options;
	t_champ		*champs;
	t_vm		*vm;

	champs = NULL;
	options = get_options(argc, argv);
	read_champions_from_args(argc, argv, &champs);
	if (champs)
	{
		vm = create_vm(champs, options);
		set_champ_code_on_arena(vm);
		//cycle(vm);
	}
	else
		ft_exit_read(USAGE, NULL, &champs, NONE);
//	print_champs(vm->champs);

 /*	проверка на файле zork.cor
	ft_printf("pos = %d\n", vm->cursors->pos);
	op_sti(vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + ARGS_SIZE + 1 + 2 + 2;
	ft_printf("and  = %d\n", vm->cursors->pos);
	op_and(vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + ARGS_SIZE + 1 + DIR_SIZE + 1;
	ft_printf("live = %d\n", vm->cursors->pos);
	op_live(vm, vm->cursors);
	vm->cursors->pos += OP_SIZE + DIR_SIZE;
	ft_printf("zjmp = %d\n", vm->cursors->pos);
	op_zjmp(vm, vm->cursors);
	ft_printf("live = %d\n", vm->cursors->pos);
	dump_arena(vm->arena);
*/
	destroy_vm(&vm);
	return (0);
}

