toolchain := arm-none-eabi
COM := COM4

# Set C compiler, can be overrided using environment variable CC
CC := $(toolchain)-gcc

# Flags (optimized for Raspberry Pi 3)
CFLAGS  := -specs=alpha/Alpha.specs -O3 -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mtune=cortex-a53
LDFLAGS := -Wl,-Talpha/link.ld -Lalpha -Wl,-umalloc -lm

.PHONY: all
all: main.elf

main.elf: main.o mpc.o mpc_codegen.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Wl,-Map,$(basename $@).map

main.o: src/main.c src/input.h
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir

mpc.o: src/mpc_build_dir/mpc.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir 

mpc_codegen.o: src/mpc_build_dir/mpc_codegen.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir

.PHONY: run
run: main.elf
	@echo "#"
	@echo "# Configure Alpha gdb stub for baud rate of 921600"
	@echo "#"
	python increase_baud.py -c $(COM)
	@echo "#"
	@echo "# Execute main.elf on remote target through $(COM)"
	@echo "#"
	@echo "target remote $(COM)" > connect_serial.gdb
	$(toolchain)-gdb -q -x run.gdb $<
	@rm connect_serial.gdb

.PHONY: clean
clean:
	rm -rf *.o *.elf *.map

.PHONY: 
test: test.elf
	@echo "#"
	@echo "# Configure Alpha gdb stub for baud rate of 921600"
	@echo "#"
	python increase_baud.py -c $(COM)
	@echo "#"
	@echo "# Execute main.elf on remote target through $(COM)"
	@echo "#"
	@echo "target remote $(COM)" > connect_serial.gdb
	$(toolchain)-gdb -q -x run.gdb $<
	@rm connect_serial.gdb

INTEGRATION_LIB := rvs_mpc/rvslib-rpi-timing
test.elf: test.c $(INTEGRATION_LIB)/rvs.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Wl,-Map,$(basename $@).map -I$(INTEGRATION_LIB) -include $(INTEGRATION_LIB)/rvs_ipoint.h -include $(INTEGRATION_LIB)/rvs.h
