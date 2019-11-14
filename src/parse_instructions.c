/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:03:59 by pcredibl          #+#    #+#             */
/*   Updated: 2019/11/15 01:02:01 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int 	get_instruct_code(char *name, t_op *op_tab)
{
	int i;
	int	code;

	i = 1;
	code = 0;
	while (i <= NUMBER_OF_INSTR)
	{
		if (!ft_strncmp(op_tab[i].name, name, ft_strlen(op_tab[i].name)))
			code = i;
		++i;
	}
	return (code);
}

static int	get_instruction(t_champ *champ, char *filedata, int i)
{
	int 		valid_code;
	t_instr		*instruct;

	//мы находимся всегда в начале команды
	//променяем валидность названия инструкции
	valid_code = get_instruct_code(&filedata[i], champ->op_tab);

	//создаем новую инструкцию
	if (valid_code)
	{
		if (!(instruct = new_instruct(&champ->op_tab[valid_code])))
			ft_exit(&champ, MALLOC_FAILURE);
	}
	else
		lexical_error(&champ, filedata, &filedata[i]);

	//сдвигаем индекс на длину команды
	i += ft_strlen(champ->op_tab[valid_code].name);

	//если после команды нет пробельного символа вызываем ошибку
	if (!ft_isspace(filedata[i]) || filedata[i] == '\n')
		lexical_error(&champ, filedata, &filedata[i]);

	i = skip_spaces(filedata, i);

	//запускаем парсинг аргументов
	i = parse_arguments(champ, instruct, filedata, i);
	return (i);
}

int			parse_instruction(t_champ *champ, char *filedata, int i)
{
	int j;

	j = 0;
	while (filedata[i])
	{
		// вначале цикла мы находимся всегда вначале строки
		// так как лейблов подряд может быть несколько
		// мы добавляем их все
		while (j != i)
		{
			i = skip_spaces(filedata, i);
			j = i;
			i = parse_label(champ, filedata, i);
		}
		// парсим инструкцию
		i = get_instruction(champ, filedata, i);
	}
	print_label(champ->labels);
	print_instruct(champ->instr);
	return (i);
}