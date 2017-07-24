obj=main.o ExpTree.o Define.o
target=main
$(target):$(obj)
	g++ $(obj) -o $(target)
%.o:%.c
	g++ -c $< -o $@
clean:
	rm -rf $(obj) 
