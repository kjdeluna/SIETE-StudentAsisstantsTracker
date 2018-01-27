main = deluna_project.c

run: $(main)
	gcc -o sample $(main)
	./sample
clean:
	rm -f $(main)
	rm -f nodeoperations.h
	rm -f logoperations.h
	rm -f functions.h
	rm -f structures.h
