obj-m += cpu_201700944_201504042.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=${PWD} modules
		
clean:
	make -C /lib/modules/$(shell uname -r)/build M=${PWD} clean