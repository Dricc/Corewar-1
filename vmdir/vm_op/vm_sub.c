#include "vm_op.h"

void vm_add(t_vm_data *data, t_vm_proc *proc, int pos)
{
    int i = 0;
    int param[3];
    int nb_octet[3];
    int ocp;

    ocp = (int)data->arena[pos % MEM_SIZE];
    proc->pc += vm_get_nb_octet(nb_octet, ocp, 4);
    if (ocp != 84)
        return ;
    while (i < 3)
    {
        param[i] = vm_get_param(data , (pos + i + 2) % MEM_SIZE, 1);
        i++;
    }
    i = 1;
    if (ft_intisbetween_inc(param[0], 0, 15) && ft_intisbetween_inc(param[1], 0, 15)
        && ft_intisbetween_inc(param[2], 0, 15))
    {
        i = ft_atoi_bigendian(proc->registre + (param[0] * REG_SIZE), REG_SIZE) - ft_atoi_bigendian(proc->registre + (param[1] * REG_SIZE), REG_SIZE);
        ft_memcpy(proc->registre + param[2] * REG_SIZE, i, REG_SIZE);
    }
    proc->carry = (int)(i == 0);
}