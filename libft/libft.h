/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 20:16:41 by rfabre            #+#    #+#             */
/*   Updated: 2018/02/06 15:59:27 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

# define DEFAULT "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define TURQUOISE "\033[36m"

# define PRESS_LEFT				4479771
# define PRESS_RIGHT			4414235
# define PRESS_UP				4283163
# define PRESS_DOWN				4348699
# define PRESS_DEL				2117294875L
# define PRESS_SPACE			32
# define PRESS_ENTER			10
# define PRESS_ESCAPE			27
# define PRESS_BACKSPACE		127
# define PRESS_STARS			42
# define PRESS_BACKSLASH		47

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_strjoinnfree(char *s1, char *s2, size_t len, char b12);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s1, int c, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_atoi(const char *str);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
		size_t len);
void				*ft_memalloc(size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_memdel(void **ap);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnew(size_t size);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_isspace(char c);
char				*ft_strtrim(char const *s);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
char				*ft_itoa(int n);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_printstrs(char **str);
void				ft_lstaddend(t_list **alst, t_list *new);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strjoinmulti(char const *s1, char const *s2,
		char const *s3);
size_t				ft_strcspn(const char *str1, char str2);
void				ft_putnstr(char const *s, size_t n);
char				*ft_freejoinstr(char *dst, char *src);
void				ft_freearraystr(char **array);
#endif
