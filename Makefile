BINDIR	:= bin
SRCDIR	:= srcs
OBJDIR	:= objs

# Define server files
FILES_S	:= server.c
SERVER	:= $(addprefix $(BINDIR)/, server)
SRCS_S	:= $(addprefix $(SRCDIR)/, $(FILES_S))
OBJS_S	:= $(addprefix $(OBJDIR)/, $(FILES_S:.c=.o))

# Define client files
FILES_C	:= client.c
CLIENT	:= $(addprefix $(BINDIR)/, client)
SRCS_C	:= $(addprefix $(SRCDIR)/, $(FILES_C))
OBJS_C	:= $(addprefix $(OBJDIR)/, $(FILES_C:.c=.o))

CC		:= cc
RM		:= rm -rf
NAME	:= minitalk
LIBFT	:= ft_printf/lib/libftprintf.a
INCDIR	:= includes
CFLAGS	:= -Wall -Wextra -Werror

all: $(LIBFT) $(BINDIR) $(OBJDIR) $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(OBJS_S) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(OBJS_C) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ft_printf

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(MAKE) -C ft_printf clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C ft_printf fclean
	$(RM) $(BINDIR)

re: fclean all

.PHONY: all clean fclean re
