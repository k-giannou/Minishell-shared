/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extras.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:00:12 by locagnio          #+#    #+#             */
/*   Updated: 2025/02/12 17:31:02 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_EXTRAS_H
# define LIBFT_EXTRAS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* typedef struct s_list
{
	void			*data;
	struct s_list	*next;
} t_list,	t_cell; */

# define RESET "\033[0m"   //Réinitialisation
# define RED   "\033[31m"   //Couleur rouge

//* free
void		free_dbl_tab(char **str);

//* maths
int			ft_sqrt(int nb);
char		*ft_itoa(int n);
int			ft_min(int *tab);
int			ft_max(int *tab);
int			ft_absolu(int nb);
int			ft_is_prime(int nb);
int			ft_find_next_prime(int nb);
int			ft_recursive_factorial(int nb);
char		*ft_itoa_base(int n, char *base);
int			ft_recursive_power(int nb, int power);
//	-conversions :
double		ft_atod(char *nptr);
float		ft_atof(char *nptr);
long		ft_atol(char *nptr);
long long	ft_atold(char *nptr);
int			ft_atoi(const char *nptr);
int			ft_natoi(const char *nptr, int *i);
int			ft_atoi_base(const char *nptr, char *base);
char		*ft_convert_base(char *nbr, char *base_from, char *base_to);
//		+ upper/lowercases :
int			ft_tolower(int c);
int			ft_toupper(int c);

//* memory allocation
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, int n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_upgrade_realloc(void *ptr, size_t size);

//* printing
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_print_dlb_tabs(char **tab);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_base(int nbr, char *base);
void		ft_putnstr_fd(char *s, int fd, int n);
void		ft_putcstr_fd(char *s, int fd, char c);

//* related to strings
//	-comparisons :
//		+ return an occurence :
char		*ft_strchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *big, const char *little, size_t len);
//		+ return the difference :
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
//	-lenght :
size_t		ft_strlen(const char *s);
size_t		ft_strclen(const char *s, char c);
//	-modifications :
char		**ft_split(char *str, char *charset);
char		*ft_strtrim(char const *s1, char const *set);
//		+ apply a function :
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//		+ concatenates :
char		*ft_strcat(char *dest, char *src);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strncat(char *dest, char *src, size_t nb);
size_t		ft_strlcat(char *dst, const char *src, size_t dsize);
char		*ft_strnjoin(char const *s1, size_t n_s1, char const *s2,
				size_t n_s2);
char		*ft_strjoin_n_free(char *s1, char *s2, int tab_to_free);
//		+ replace dest by src :
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dsize);
//		+ set a string :
void		*ft_memset(void *s, int c, size_t n);
char		*ft_remove_from_string(char *str, char *to_delete);

//* verifications
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_strnchr(const char *s, const char *to_find, int len);

/* // chain lists
long		len_list(t_list *L);
void		print_list(t_list *L);
t_cell		*create_cell(void *data);
t_list		*ft_listdup(t_list *src);
void		*get_at(t_list *L, int pos);
t_list		*ft_listndup(t_list *src, int n);
void		ft_list_sort(t_list **begin_list);
void		ft_list_reverse(t_list **begin_list);
void		set_at(t_list *L, void *data, int pos);
t_list		*add_at(t_list *L, void *data, int pos);
void		ft_list_add_front(t_list **lst, t_list *new);
void		ft_list_add_back(t_list **lst, t_list *new);
int			ft_list_find_pos(t_list *begin_list, void *data_ref);
void		ft_list_remove_if(t_list **begin_list, void *data_ref);
int			ft_list_find_data(t_list *begin_list, void *data_ref);
void		ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void		ft_list_foreach_data(t_list *begin_list, void (*f)(void *));
void		ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2);
void		ft_list_foreach_data_if(t_list *begin_list, void (*f)(void *), \
void *data_ref);
//	-free lists :
void		free_list(t_list *L);
t_list		*free_at(t_list *L, int pos); */

#endif