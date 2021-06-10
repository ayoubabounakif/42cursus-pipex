# STILL NEEDS FIXING

FLAGS = 

LIBNAME = libft.a

NAME = pipex

EXEC = pipex

SRC = pipex.c env.c fork_pipes.c

all: $(NAME)

$(LIBNAME): $(SRC)
	make -C libft/
	cp libft/$(LIBNAME) ./

$(NAME): $(LIBNAME)
	@echo "Compilation in progress! DO NOT INTERRUPT!"
	gcc -g3 -fsanitize=address $(FLAGS) $(SRC) libft.a dlist/*.c -D BUFFER_SIZE=1024 -o $(EXEC)
	@echo "Compilation done! :)"

clean:
	make clean -C libft/
	rm -f *.o

fclean: clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(EXEC)

re: fclean all