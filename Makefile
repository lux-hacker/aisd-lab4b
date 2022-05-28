all: build tree.a view.o controller.o main.o
	cc -o lab4b build/*.o -lreadline -L./build -ltree -std=c11 -g

timing: build tree.a view.o controller.o timnig.o
	cc -o timing build/*.o -lreadline -L./build -ltree -std=c11 -g

counter: build tree.a view.o controller.o counter.o
	cc -o counter build/*.o -lreadline -L./build -ltree -std=c11 -g

build:
	mkdir build

tree.a: model.o
	ar rcs build/libtree.a build/RBTree.o
	rm build/RBTree.o

main.o:
	cc -c main.c -o build/main.o -std=c11 -g

timnig.o:
	cc -c timing.c -o build/timnig.o -std=c11 -g

counter.o:
	cc -c counter.c -o build/counter.o -std=c11 -g

model.o:
	cc -c model/RBTree.c -o build/RBTree.o -std=c11 -g

view.o:
	cc -c view/view.c -o build/view.o -std=c11 -g

controller.o:
	cc -c controller/controller.c -o build/controller.o -std=c11 -g

clean:
	rm -rf build/
	rm lab4b

clean_timing:
	rm -rf build/
	rm timing

clean_counter:
	rm -rf build/
	rm counter
