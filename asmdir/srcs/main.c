/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/03/29 10:38:36 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_list		*lex;
	t_buf		buffer_header;
	t_buf		buffer_prog;
	header_t	header;
	t_list		*label;

	if (ac != 2)
		return (0);
	buffer_header.data = NULL;
	buffer_header.size = 0;
	buffer_prog.data = NULL;
	buffer_prog.size = 0;
	label = NULL;
//Lexer
	ft_printf("PROGRAM STARTED\n");
	lex = get_lex(av[1]);
	ft_printf("get_lex OK\n");
	set_lex(lex, &label);
	ft_printf("Set_lex OK\n");
	if (!lex)
		ft_printf("ERROR LEX IS NULL\n");
//Parser
	parse(lex, label);
//Affichage && Debug
	ft_lstiter(lex, &debug_lxcontent);
	ft_lstiter(label, &debug_labelcontent);
//Ecriture du player
	ft_memset(header.prog_name, 0, PROG_NAME_LENGTH);
	ft_memset(header.comment, 0, COMMENT_LENGTH);
	ft_strcpy(header.prog_name, "This is a test !");
	ft_strcpy(header.comment, "COMMENT TEST !");
	header.magic = COREWAR_EXEC_MAGIC;
	header.prog_size = 0x1d000000;
	header_to_buffer(&buffer_header, &header);
	write_player(&buffer_prog, lex, label);
	write_to_buffer(&buffer_header, buffer_prog.data, buffer_prog.size);
	write_bin("player.cor", &buffer_header);
//Free lst-> Lx && Label
	ft_lstdel(&lex, &del_lex);
	ft_lstdel(&label, &del_label);
	ft_printf("PROGRAM FINISHED\n");
	return (0);
}
