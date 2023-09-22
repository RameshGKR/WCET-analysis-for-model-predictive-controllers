# Get settings required to deploy to Raspberry Pi with Alpha
source alpha/alpha.gdb

# Connect to the RPi
set serial baud 921600
source connect_serial.gdb

# Load the executable to the target
load

# Quit on SIGTRAP (by default at end of executable)
catch signal SIGTRAP
commands
    quit
end

# Run
continue




