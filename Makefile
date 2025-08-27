NAME := dns-resolve
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iincludes
SRCS := src/util.c src/main.c 
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(NAME)

re: clean all
