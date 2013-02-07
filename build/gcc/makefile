all:
	make -C ../../src/
	make -C ../../src/ install
	make -C ../../test/

rebuild: clean all

install:
	make -C ../../test/ install 

uninstall:
	make -C ../../src/ uninstall
	make -C ../../test/ uninstall 

clean:
	make -C ../../src/ clean
	make -C ../../test/ clean
