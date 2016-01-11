/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 04:51:48 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/11 19:55:48 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_putnbr_ulong(unsigned long long int num, t_list_p *list)
{
	unsigned int	i;

	i = 0;
	if (!list->prec && list->prec_i)
		return (0);
	list->prec_i = 0;
	while (list->prec > ft_putnbr_ulong_len(num))
	{
		if (list->modifi_atoi)
			i += write(1, " ", 1);
		else
			i += write(1, "0", 1);
		list->prec--;
	}
	list->prec = 0;
	if (num / 10)
		i += ft_putnbr_ulong(num / 10, list);
	ft_putchar((num % 10) + '0');
	return (i + 1);
}
void				ft_zebi(long long int num, t_list_p *list)
{
	if (list->modifi_atoi > 0 && !list->prec)
		list->modifi_atoi = list->modifi_atoi - ft_putnbr_ulong_len(num);
	else if (list->modifi_atoi > 0 && (list->prec < ft_putnbr_ulong_len(num)))
		list->modifi_atoi -= ft_putnbr_ulong_len(num);
	else if (list->modifi_atoi > 0 && (list->prec > list->modifi_atoi))
		list->modifi_atoi = 0;
	else if (list->modifi_atoi > 0 && (list->chr || (list->modifi_atoi >
					(list->prec + ft_putnbr_ulong_len(num)))))
		list->modifi_atoi -= list->prec;
	else if (list->modifi_atoi > 0)
		list->modifi_atoi -= ft_putnbr_ulong_len(num);
}

void				ft_zebi_nega(long long int num, t_list_p *list)
{
	if (list->modifi_atoi > 0 && !list->prec)
		list->modifi_atoi = list->modifi_atoi - (ft_putnbr_ulong_len(num) - 1);
	else if (list->modifi_atoi > 0 && (list->prec < (ft_putnbr_ulong_len(num) + 1)))
		list->modifi_atoi = list->modifi_atoi - 1; //+ ft_putnbr_ulong_len(num);
	else if (list->modifi_atoi > 0 && (list->prec > list->modifi_atoi))
	{
		list->modifi_atoi = 0;//list->prec - (ft_putnbr_ulong_len(num) + 1);
		list->chr = 1;
	}
	else if (list->modifi_atoi > 0)
		list->modifi_atoi -= (ft_putnbr_ulong_len(num) + 1);
}

int					ft_print_num_d(t_list_p *list, void *params)
{
	long long int	num;
	int				i;
	int				tmp2;

	if (list && list->modifi_l == 1)
		num = va_arg(*((va_list *)params), long int);
	else if (list && list->modifi_l == 2)
		num = va_arg(*((va_list *)params), long long int);
	else if (list && list->modifi_h == 2)
		num = (char)va_arg(*((va_list *)params), int);
	else if (list && list->modifi_j == 1)
		num = va_arg(*((va_list *)params),long int);
	else if (list && list->modifi_z == 1)
		num = va_arg(*((va_list *)params), size_t);
	else
		num = va_arg(*((va_list *)params), int);
	i = 0;
	if ((!num) && (list->dize))
		i = write(1, "0", 1);
	tmp2 = list->modifi_atoi;
	if (num < 0)
	{
		num *= -1;
		ft_zebi_nega(num, list);
		i += list->chr ? write(1, "-", 1) : 0;
		if (list->modifi_atoi > 0)
			i += ft_write_space(list->modifi_atoi - (ft_putnbr_ulong_len(num)), list);
		i += list->chr ? ft_putnbr_ulong(num, list) : write(1, "-", 1) + ft_putnbr_ulong(num, list);
		return (i + ft_write_space((tmp2 + i) * -1, list));
	}
	i += list->space && !list->p ? write(1, " ", 1) : 0;
	i += list->p ? write(1, "+", 1) : 0;
	ft_zebi(num, list);
	i += (list->modifi_atoi > 0) ? ft_write_space((list->modifi_atoi), list) : 0;
	return  ((ft_putnbr_ulong(num, list) + i) +
			ft_write_space(((tmp2 + ft_putnbr_ulong_len(num)) * -1), list));
}

int					ft_print_num_d_height_u_int(t_list_p *list, void *params)
{
	int				i;
	long			num;

	i = 0;
	if (list && list->modifi_l == 1)
		num = va_arg(*((va_list *)params), unsigned long int);
	else if (list && list->modifi_l == 2)
		num = va_arg(*((va_list *)params), unsigned long long int);
	else if (list && list->modifi_h == 2)
		num = (unsigned char)va_arg(*((va_list *)params), int);
	else if (list && list->modifi_j == 1)
		num = (unsigned long)va_arg(*((va_list *)params), long);
	else if (list && list->modifi_z == 1)
		num = va_arg(*((va_list *)params), size_t);
	else
		num = va_arg(*((va_list *)params), unsigned int);
	ft_zebi(num, list);
	i += (list->modifi_atoi > 0) ? ft_write_space((list->modifi_atoi), list) : 0;
	return (ft_putnbr_ulong(num, list) + i);
}

int					ft_print_num_d_height_u_long(t_list_p *list, void *params)
{
	unsigned long		num;

	(void)list;
	num = va_arg(*((va_list *)params), unsigned long);
	return (ft_putnbr_ulong(num, list));
}

int					ft_print_num_d_height_long(t_list_p *list, void *params)
{
	long int		num;

	(void)list;
	num = va_arg(*((va_list *)params), long int);
	if (num < 0)
	{
		ft_putchar('-');
		return (ft_putnbr_ulong(num * -1, list) + 1);
	}
	return (ft_putnbr_ulong(num, list));
}
