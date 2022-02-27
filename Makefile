BINDIR	:= bin
SRCDIR	:= srcs
OBJDIR	:= objs

# Define server files
FILES_S	:= main.c sig_handler.c setup_sigaction.c \
		   store_bits.c send_signal_to_client.c
SERVER	:= $(BINDIR)/server
SRCS_S	:= $(addprefix $(SRCDIR)/server/, $(FILES_S))
OBJS_S	:= $(addprefix $(OBJDIR)/server/, $(FILES_S:.c=.o))
DEPS_S	:= $(addprefix $(OBJDIR)/server/, $(FILES_S:.c=.d))

# Define client files
FILES_C	:= main.c parse_pid.c sig_handler.c \
		   send_char.c send_message.c
CLIENT	:= $(BINDIR)/client
SRCS_C	:= $(addprefix $(SRCDIR)/client/, $(FILES_C))
OBJS_C	:= $(addprefix $(OBJDIR)/client/, $(FILES_C:.c=.o))
DEPS_C	:= $(addprefix $(OBJDIR)/client/, $(FILES_C:.c=.d))

CC		:= cc
RM		:= rm -rf
NAME	:= minitalk
LIBFT	:= ft_dprintf/lib/libftdprintf.a
INCDIR	:= ft_dprintf/includes ft_dprintf/libft/includes includes
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP

all: $(LIBFT) $(BINDIR) $(OBJDIR) $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(OBJS_S) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(OBJS_C) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(addprefix -I, $(INCDIR)) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ft_dprintf

$(BINDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@/server $@/client

clean:
	$(MAKE) -C ft_dprintf clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C ft_dprintf fclean
	$(RM) $(BINDIR)

re: fclean all

-include $(DEPS_S) $(DEPS_C)

.PHONY: all clean fclean re
