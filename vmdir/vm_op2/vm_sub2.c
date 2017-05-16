/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:00:13 by lduval            #+#    #+#             */
/*   Updated: 2017/05/10 03:19:05 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_sub2(t_vm_data *data, t_vm_proc *proc, int *param, int *nb_octet)
{
	int i;
	int j;

	i = 1;
	if (ft_intisbetween_inc(param[0], 0, 15) && ft_intisbetween_inc(param[1], 0, 15)
			&& ft_intisbetween_inc(param[2], 0, 15))
	{
		ft_memcpy(&i, proc->registre + (param[0] * REG_SIZE), REG_SIZE);
		ft_memcpy(&j, proc->registre + (param[1] * REG_SIZE), REG_SIZE);
		i -= j;
		ft_memcpy(proc->registre + param[2] * REG_SIZE, &i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
	(void)nb_octet;
	(void)data;
}