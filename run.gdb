source alpha/alpha.gdb

# Connect to the RPi
set serial baud 921600
source connect_serial.gdb

# Load the executable in the target
# By default, the loaded file is the one GDB debugs, given as argument
# to gdb or using the command file.
load

# Quit on SIGTRAP
catch signal SIGTRAP
commands
    quit
end

# Run
continue




