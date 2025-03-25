/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:05:11 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/20 15:38:21 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	parser(int i, int *count, t_struct v, va_list args)
{
	if (v.str[i] == 'c')
		ft_print_char((char)va_arg(args, int), v, count);
	else if (v.str[i] == 's')
		ft_print_str(va_arg(args, char *), v, count);
	else if (v.str[i] == 'p')
		ft_print_ptr((size_t)va_arg(args, void *), v, count);
	else if (v.str[i] == 'd' || v.str[i] == 'i')
		ft_print_int(va_arg(args, int), v, count);
	else if (v.str[i] == 'u')
		ft_print_uns_int(va_arg(args, int), v, count);
	else if (v.str[i] == 'x' || v.str[i] == 'X')
		ft_print_hexa(va_arg(args, int), v, i, count);
	else if (v.str[i] == '%')
		ft_print_percent('%', count, v.fd);
}

int	parse_nd_flags(int i, int *count, t_struct v, va_list args)
{
	while (!standard_conds(v, i))
	{
		if ((v.str[i] >= '1' && v.str[i] <= '9') || v.str[i] == '.'
			|| v.str[i] == '*')
			v = parse_nd_flags2(&i, v, args);
		else
		{
			v = flags(bonus_flag_finder(i, v), v);
			i += 1;
		}
	}
	if (v.nb1 < 0)
	{
		v = flags('-', v);
		v.nb1 = -v.nb1;
	}
	v = flag_filter(i, v);
	parser(i, count, v, args);
	return (i);
}

int	print_this_bs(va_list args, t_struct v)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (v.str[i])
	{
		if (v.str[i] == '%')
			i = parse_nd_flags(i + 1, &count, v, args);
		else
		{
			write(v.fd, &v.str[i], 1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list		args;
	t_struct	v;
	int			count;
	int			i;

	if (!str)
		return (0);
	i = 0;
	v.str = str;
	while (i < 7)
		v.flags[i++] = 0;
	v.nb1 = 0;
	v.nb2 = 0;
	v.zeros = 0;
	v.fd = fd;
	va_start(args, str);
	count = print_this_bs(args, v);
	va_end(args);
	return (count);
}

/* #include <limits.h>
#include <stdio.h>

int	main(void)
{
	printf("original : %d\n", printf("original : |^.^/%-15.6s^.^/|\n", NULL));
	fflush(stdout);
	printf("copie    : %d\n", ft_fprintf(1, "copie    : |^.^/%-15.5s^.^/|\n", NULL));
	printf("\n\n\n");
	return (0);
} */

/*
"%#-76.67x%-178c%#126.17x%-178.97%%-80.63i" ,2705358650u,-128,4292242043u,
-156704363
"%-26.85u%+#100.2%%#0130.74x%#59.63X%086x" ,602620792u,1774300267u,835967277u
,2887108754u
"%64.79u%#168.142x%110c" ,1663238694u,2980990023u,-98
"%--99p%94.103s%181.150x% 21d%+16.%" ,17804030627542756824lu,"\n#\fj<Oil\ft7\
tj&^|ddD80t\nIL+,",184469023u,1795574960
"%#73.181X%--47.192X" ,3720784993u,3491116485u
"%-#88.82x" ,3532279970u
"%#196.53X" ,3130516526u
"%  130.137%%#102.18x%059.56u%#167.193X" ,2661836307u,3540858512u,1574239099u
"% 171.152d%p%0197.33u%0+#131.71%" ,2055571139,6109035435017027490lu,
1457993623u
"%98p%147p%#43.85x%++197.126i%195.u" ,17422923310524768300lu,
8561336791391148915lu,839088623u,-1692713526,2802635555u
"%.80s% # 177.44%%#093.105X" ,"Nhfxl\\f}EJyv:>\tgq7kFZ&VUM",392767992u
"%#38.119x%120p%155c%-147.d" ,4216448853u,12423865882424705706lu,-98,
-1967106559
"%48c%-#184.95X%185p" ,48,856683944u,9125943193160606356lu */