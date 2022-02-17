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
NAME	:= minitalk
INCDIR	:= includes
CFLAGS	:= -Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(OBJS_S)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT): $(OBJS_C)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) $(OBJS_S) $(OBJS_C)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
