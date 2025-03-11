/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:00:12 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/04 14:00:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_struct
{
	const char	*str;
	char		flags[7];
	int			nb1;
	int			nb2;
	int			zeros;
	int			fd;
}	t_struct;

int			ft_digits(long n);
int			ft_atoi(const char *nptr);
int			srch_flag(char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_fprintf(int fd, const char *str, ...);
int			standard_conds(t_struct v, int i);
int			print_this_bs(va_list args, t_struct v);
char		bonus_flag_finder(int i, t_struct v);
void		ft_putnbr(long n, t_struct v, long base, long print);
void		ptr_print(size_t nb, t_struct v);
void		ft_putunbr(unsigned long n, t_struct v);
void		ft_putstr(char *s, int *count, int limit, int fd);
void		hexa_print(unsigned int nb, t_struct v, char x);
void		ft_print_char(char c, t_struct v, int *count);
void		ft_print_int(long nb, t_struct v, int *count);
void		ft_print_hexa(unsigned int nb, t_struct v, int i, int *count);
void		ft_print_str(char *str, t_struct v, int *count);
void		ft_print_ptr(size_t ptr, t_struct v, int *count);
void		ft_print_uns_int(long nb, t_struct v, int *count);
void		ft_print_percent(char percent, int *count, int fd);
size_t		ft_strlen(const char *s);
t_struct	flag_filter(int i, t_struct v);
t_struct	flags(char c, t_struct v);
t_struct	erase_flag(char erased, t_struct v);
t_struct	parse_nd_flags2(int *i, t_struct v, va_list args);
t_struct	keep_prior_flag(char erased, char prior, t_struct v);

#endif