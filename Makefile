toolchain := arm-none-eabi

# Set default C compiler, override using environment variable
CC := $(toolchain)-gcc

# Set default COM port of Raspberry Pi, override using environment variable or command line
COM := COM4

# Flags: configured to use Alpha GDB stub, optimized for Raspberry Pi 3
CFLAGS  := -specs=alpha/Alpha.specs -O3 -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mtune=cortex-a53
LDFLAGS := -Wl,-Talpha/link.ld -Lalpha -Wl,-umalloc -lm

# Default target
.PHONY: all
all: main.elf

# Executable: linking stage
main.elf: main.o mpc.o mpc_codegen.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Wl,-Map,$(basename $@).map

# Objects: compilation stage
main.o: src/main.c src/input.h
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir

mpc.o: src/mpc_build_dir/mpc.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir 

mpc_codegen.o: src/mpc_build_dir/mpc_codegen.c
	$(CC) -c $^ -o $@ $(CFLAGS) $(LDFLAGS) -Isrc/mpc_build_dir

# Deploy executable to Raspberry Pi: boot files required on SD card, specify COM port
.PHONY: run
run: main.elf
	@echo "#"
	@echo "# Configure Alpha gdb stub for baud rate of 921600"
	@echo "#"
	python increase_baud.py -c $(COM)
	@echo "#"
	@echo "# Execute $< on remote target through $(COM)"
	@echo "#"
	@echo "target remote $(COM)" > connect_serial.gdb
	$(toolchain)-gdb -q -x run.gdb $<
	@rm connect_serial.gdb

# Clean generated files
.PHONY: clean
clean:
	rm -rf *.o *.elf *.map

# Test executable: compiling and linking 
INTEGRATION_LIB := rvs_mpc/rvslib-rpi-timing
test.elf: test.c $(INTEGRATION_LIB)/rvs.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Wl,-Map,$(basename $@).map -I$(INTEGRATION_LIB) -include $(INTEGRATION_LIB)/rvs_ipoint.h -include $(INTEGRATION_LIB)/rvs.h

# Deploy test executable to Raspberry Pi: boot files required on SD card, specify COM port
.PHONY: test
test: test.elf
	@echo "#"
	@echo "# Configure Alpha gdb stub for baud rate of 921600"
	@echo "#"
	python increase_baud.py -c $(COM)
	@echo "#"
	@echo "# Execute $< on remote target through $(COM)"
	@echo "#"
	@echo "target remote $(COM)" > connect_serial.gdb
	$(toolchain)-gdb -q -x run.gdb $<
	@rm connect_serial.gdb
