BINDIR	:= bin
SRCDIR	:= srcs
OBJDIR	:= objs

# Define server files
FILES_S	:= main.c
SERVER	:= $(BINDIR)/server
SRCS_S	:= $(addprefix $(SRCDIR)/server/, $(FILES_S))
OBJS_S	:= $(addprefix $(OBJDIR)/server/, $(FILES_S:.c=.o))

# Define client files
FILES_C	:= main.c
CLIENT	:= $(BINDIR)/client
SRCS_C	:= $(addprefix $(SRCDIR)/client/, $(FILES_C))
OBJS_C	:= $(addprefix $(OBJDIR)/client/, $(FILES_C:.c=.o))

CC		:= cc
RM		:= rm -rf
NAME	:= minitalk
LIBFT	:= ft_dprintf/lib/libftdprintf.a
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
	$(MAKE) -C ft_dprintf

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@
	mkdir -p $@/client
	mkdir -p $@/server

clean:
	$(MAKE) -C ft_dprintf clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C ft_dprintf fclean
	$(RM) $(BINDIR)

re: fclean all

.PHONY: all clean fclean re
