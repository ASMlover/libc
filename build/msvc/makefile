all:
	chdir ..\..\src
	nmake -f makefile.win
	nmake -f makefile.win install
	chdir ..\test
	nmake -f makefile.win

rebuild: clean all

install:
	chdir ..\..\test
	nmake -f makefile.win install

uninstall:
	chdir ..\..\src
	nmake -f makefile.win uninstall 
	chdir ..\test
	nmake -f makefile.win uninstall 

clean:
	chdir ..\..\src
	nmake -f makefile.win clean
	chdir ..\test
	nmake -f makefile.win clean
