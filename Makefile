all: dusk duskrc

dusk:
	cd Dusk; make

duskrc:
	cd DuskRC; make

clean:
	cd Dusk; make clean
	cd DuskRC; make clean

.PHONY: dusk duskrc
