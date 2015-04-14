all: dusk duskrc

dusk:
	cd Dusk; make

duskrc:
	cd DuskResourceManager; make

clean:
	cd Dusk; make clean
	cd DuskResourceManager; make clean

.PHONY: dusk duskrc
