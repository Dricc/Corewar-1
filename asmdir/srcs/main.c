/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:45:22 by czalewsk          #+#    #+#             */
/*   Updated: 2017/05/04 10:16:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list			*lex;
t_list			*label;
t_buf			buffer_header;
t_buf			buffer_prog;

extern	t_list	*g_files;

void			del_g_files(void *content, size_t size)
{
	(void)size;
	ft_strdel((char**)content);
	free(content);
}

void			sp_free(t_list *lex, t_list *label, t_buf *buffer1,
		t_buf *buffer2)
{
	if (lex)
		ft_lstdel(&lex, &del_lex);
	if (label)
		ft_lstdel(&label, &del_label);
	if (g_files)
		ft_lstdel(&g_files, &del_g_files);
	if (buffer1->data)
		free(buffer1->data);
	if (buffer2->data)
		free(buffer2->data);
}

void			main_error(char *str, int forcequit)
{
	ft_printf("{red}%s{eoc}\n", str);
	sp_free(lex, label, &buffer_header, &buffer_prog);
	if (forcequit)
		exit(1);
}

void			buffer_init(t_buf *buffer1, t_buf *buffer2,
		header_t *header, char *name)
{
	buffer1->data = NULL;
	buffer1->size = 0;
	buffer2->data = NULL;
	buffer2->size = 0;
	ft_memset(header->comment, 0, COMMENT_LENGTH);
	ft_memset(header->prog_name, 0, PROG_NAME_LENGTH);
	ft_strcpy(header->prog_name, "DEFAULT_NAME_");
	ft_strncat(header->prog_name, name, PROG_NAME_LENGTH);
	ft_strcpy(header->comment, "DEFAULT_CMT");
}

void			print_line(t_list *lst)
{
	ft_printf("%s\n", *(char**)lst->content);
}

void			do_stuff(int i, char *av)
{
	header_t	header;

	buffer_init(&buffer_header, &buffer_prog, &header, av);
	label = NULL;
//Lexer
	(lex = get_lex(av)) ? 1 : main_error("get_lex error", 1);
	set_lex(lex, &label);
//Parser
	parse(lex, label, &header);
//Affichage && Debug
	i ? ft_lstiter(lex, &debug_lxcontent) : 0;
	i ? ft_lstiter(label, &debug_labelcontent) : 0;
	i ? ft_lstiter(g_files, &print_line) : 0;
//Error Manager
	if (check_error(lex))
		main_error("Error in lexer/parser\nProgramm hasn't finished", 1);
//Ecriture du player
	write_player(&buffer_prog, lex, label, &header);
	header_to_buffer(&buffer_header, &header);
	write_to_buffer(&buffer_header, buffer_prog.data, buffer_prog.size);
	write_bin(av, &buffer_header);
//Free lst-> Lx && Label
	sp_free(lex, label, &buffer_header, &buffer_prog);
	ft_printf("{green}PROGRAM FINISHED{eoc}\n");
}

void			do_stuff_reverse(char *av)
{
	t_vm_champ	*champ;

	if (!(champ = (t_vm_champ *)ft_memalloc(sizeof(t_vm_champ))))
		return ;
	vm_read_champ(av, champ);
	write_player_reverse(av, champ);
}

int				main(int ac, char **av)
{
	int		arg;
	int		i;

	arg = 0;
	i = 1;
	while (i < ac && ac > 1)
	{
		if (av[i][0] == '-')
		{
			if (!ft_strcmp(av[i], "-r"))
				arg = arg | 1;
		}
		else if (arg == 0)
			do_stuff(1, av[i]);
		else if (arg & 1)
			do_stuff_reverse(av[i]);
		++i;
	}
	return (0);
}
