/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduval <lduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 09:48:36 by lduval            #+#    #+#             */
/*   Updated: 2017/05/03 12:24:02 by lduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_op.h"

void	vm_lldi(t_vm_data *data, t_vm_proc *proc, int pos)
{
	int				i;
	int				param[3];
	int				nb_octet[3];
	unsigned int	ocp;
	int				tmp;

	i = 0;
	ocp = (unsigned int)data->arena[(pos + 1) % MEM_SIZE];
	proc->pc += vm_get_nb_octet(nb_octet, ocp, 13);
	if (!vm_check_param(ocp, 13))
		return ;
	param[0] = vm_get_param(data, (pos + 2) % MEM_SIZE, nb_octet[0]);
	param[1] = vm_get_param(data, (pos + 2 + nb_octet[0]) % MEM_SIZE, nb_octet[1]);
	param[2] = vm_get_param(data, pos + 2 + nb_octet[0] + nb_octet[1], nb_octet[2]);
	i = 1;
	if (ft_intisbetween_inc(param[2], 0, 15) && (((ocp >> 2) & 3) != 1 || ft_intisbetween_inc(param[0], 0, 15)))
	{
		while (i < 3)
		{
			if (((ocp >> (2 * (i + 1))) & 3) == 1)
				param[i] = ft_atoi_bigendian(proc->registre + (param[i] * REG_SIZE), REG_SIZE);
			else
				(((ocp >> (2 * (i + 1))) & 3) == 2) ? false :
					(tmp = vm_get_param(data, pos + (param[i] % IDX_MOD)) && ft_memcpy(param + i, &tmp , REG_SIZE), REG_SIZE);
			i++;
		}
		i = param[0] + param[1];
		ft_memcpy(proc->registre + param[2] * REG_SIZE, data->arena + pos + i, REG_SIZE);
	}
	proc->carry = (int)(i == 0);
}