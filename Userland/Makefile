include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: libc sampleCodeModule sampleDataModule shell

libc:
	cd Libc; make

sampleCodeModule:
	cd SampleCodeModule; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

shell:
	cd Shell; make

clean:
	cd SampleCodeModule; make clean
	cd Shell; make clean
	cd Libc; make clean
	rm -rf *.bin


.PHONY: sampleCodeModule all clean
