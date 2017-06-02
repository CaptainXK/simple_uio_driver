.PHONY:clean,test

test:test.app
	@$(EXEC) ./test.app
test.app:user_part.o
	@gcc user_part.o -o test.app
user_part.o:user_part.c
	@gcc -c user_part.c -g3
clean:
	@rm *.o *.app
