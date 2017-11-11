/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:39:11 by acorbeau          #+#    #+#             */
/*   Updated: 2017/11/01 13:50:01 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "xdef.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 4096

# define ERR_NOFOUND 1
# define ERR_NOACCESS 2
# define ERR_NOCMD 3
# define ERR_FORK 4
# define ERR_NOTOKEN 5
# define ERR_UNEXPCT 6
# define ERR_ENDOFF 7

# define XMAP_MAX 32
# define XMAP_SIZE 4094

# define XGET      0
# define XCREATE   1
# define XEXTENDE  2
# define XFREE	   3
# define XDEFRAG   4

# define XF_NONE     0
# define XF_OCCUPIED 1

typedef	struct		s_xmap
{
	void			**map;
	int				flags;
	size_t			ptr;
	size_t			size;
}					t_xmap;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_perror(char *str, int flags);
void				ft_errset(char *name);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_max(int a, int b);
int					ft_isspace(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_ispunct(int c);
int					ft_isblank(int c);

int					ft_nlen(int n);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *a, const char *b);
int					ft_strncmp(const char *a, const char *b, size_t n);

char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t siz);
char				*ft_strdup(const char *str);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *str, const char *find);
char				*ft_strnstr(const char *str, const char *find, size_t n);

void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int n);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putnbr_fd(int n, int fd);

void				*ft_memdup(void *data, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_tabdel(char ***t);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_segcount(char const *s, char c);
size_t				ft_seglen(char const *s, char c);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstcreate(void *content, size_t content_size);
void				ft_lstdelone(t_list **root, void (*f)(void *, size_t));
void				ft_lstdel(t_list **root, void (*f)(void *, size_t));
void				ft_lstadd(t_list **root, t_list *item);
void				ft_lstaddfront(t_list **root, t_list *new);
void				ft_lstiter(t_list *root, void (*f)(t_list *item));
t_list				*ft_lstmap(t_list *root, t_list *(f)(t_list *item));
void				ft_lstpop(t_list **root);
void				ft_lstswap(t_list *lst1, t_list *lst2);
void				ft_lstsort(t_list *root, int (*f)(t_list *, t_list *));
void				ft_lstrev(t_list **alst);

char				*ft_strjoin_at(char *s1, char *s2, int i);
int					ft_sc(char *str, char c);
int					ft_snc(char *str, char c, int size);
int					ft_pow(int n, int p);
char				*ft_strndup(const char *s1, size_t size);
char				*ft_str3join(char *s1, char *s2, char *s3);

char				*ft_xstrdup(const char *str, int ref);
char				*ft_xstrsub(char const *s, unsigned int start, \
		size_t len, int ref);
void				*ft_salloc(size_t size);
void				*ft_scalloc(size_t size);
void				*ft_xalloc(size_t size, int ref);
void				*ft_xcalloc(size_t size, int ref);

t_xmap				*ft_xmap(int ref, int mode);
void				ft_xfree(void *ptr, int ref);
void				ft_xclear(int ref);
t_list				*ft_xlstcreate(void *content, size_t content_size, int ref);
t_list				*ft_xlstnew(void *content, size_t content_size, int ref);

int					get_next_line(int fd, char **line);
int					xget_next_line(int fd, char **line, int ref);

void				ft_capitalizer(char *s);
uintmax_t			ft_power(int n, int p);
size_t				ft_wbytelen(wchar_t *ws);
int					ft_wcharlen(wchar_t wchar);
size_t				ft_wstrlen(wchar_t *ws);

char				*ft_char_itoa_base(signed char nb, int base);
char				*ft_itoa_base(int nb, int base);
char				*ft_litoa_base(long int nb, int base);
char				*ft_llitoa_base(long long int nb, int base);
char				*ft_max_itoa_base(intmax_t nb, int base);
char				*ft_short_itoa_base(short int nb, int base);
char				*ft_size_itoa_base(size_t nb, int base);
char				*ft_uchar_itoa_base(unsigned char nb, int base);
char				*ft_uitoa_base(unsigned int nb, int base);
char				*ft_ulitoa_base(unsigned long int nb, int base);
char				*ft_ullitoa_base(unsigned long long int nb, int base);
char				*ft_umax_itoa_base(uintmax_t nb, int base);
char				*ft_ushort_itoa_base(unsigned short int nb, int base);
#endif
