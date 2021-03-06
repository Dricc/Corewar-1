/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_verb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 05:04:20 by lduval            #+#    #+#             */
/*   Updated: 2017/05/23 06:29:11 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void		vm_lns_verb(t_vm_proc *proc, int *param)
{
	int			i;
	t_vm_data	*data;
	t_vm_champ	*champ;

	champ = NULL;
	if (proc->next_op == 1)
	{
		i = -1;
		data = get_data();
		while (!champ && data->tab_champ[++i])
			if (data->tab_champ[i]->num == param[0])
				champ = data->tab_champ[i];
	}
	if (champ)
		ft_printf("Player %d (%s) is said to be alive\n",
			champ->posnum, champ->header.prog_name);
	if (proc->next_op == 0xb)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			param[1], param[2], param[1] + param[2],
			(proc->pc + param[1] + param[2]) % MEM_SIZE);
	else if (proc->next_op == 0xa)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			param[0], param[1], param[0] + param[1],
			(proc->pc + param[0] + param[1]) % MEM_SIZE);
}

void		vm_adv_verb(t_vm_proc *proc, int *nb_octet)
{
	int			i;
	int			j;
	t_vm_data	*data;
	int			l;

	j = -1;
	data = get_data();
	i = nb_octet[0] + nb_octet[1] + nb_octet[2];
	i += proc->ocp ? 1 : 0;
	i++;
	while (proc->pc < 0)
		proc->pc += MEM_SIZE;
	while (proc->pc > MEM_SIZE)
		proc->pc -= MEM_SIZE;
	l = proc->pc + i;
	while (l < 0)
		l += MEM_SIZE;
	while (l > MEM_SIZE)
		l -= MEM_SIZE;
	ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", i, proc->pc, proc->pc + i);
	while (++j < i)
		ft_printf("%.2x ", data->arena[(proc->pc + j) % MEM_SIZE]);
	ft_printf("\n");
}

void		vm_verb(t_vm_proc *proc, int *param, int *nb_octet)
{
	int i;

	if (get_data()->option & VM_OPT_V)
	{
		i = 0;
		ft_printf("P %4d | %s", proc->nproc, g_op_tab[proc->next_op - 1].name);
		while (i < 3 && nb_octet[i])
		{
			if (nb_octet[i] == 1 && (proc->next_op != 0xb || i != 2))
				ft_printf(" r%d", param[i]);
			else
				ft_printf(" %d", param[i]);
			i++;
		}
		if (proc->next_op == 9)
			proc->carry ? ft_printf(" OK") : ft_printf(" FAILED");
		if (proc->next_op == 0xc || proc->next_op == 0xf)
			ft_printf(" (%d)", proc->pc + param[0]);
		ft_printf("\n");
		vm_lns_verb(proc, param);
		if (proc->next_op != 9 || !proc->carry)
			vm_adv_verb(proc, nb_octet);
	}
}
