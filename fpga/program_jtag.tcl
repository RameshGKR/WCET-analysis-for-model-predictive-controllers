# Constants
set deviceName xc7a35t_0
set outputDir out

# Connect to hardware manager
open_hw_manager
connect_hw_server -allow_non_jtag

# Connect to target
open_hw_target
current_hw_device [get_hw_devices $deviceName]
refresh_hw_device -update_hw_probes false [current_hw_device]

# Program
set_property PROGRAM.FILE [list "$outputDir/top.bit"] [current_hw_device]
program_hw_devices [current_hw_device]
refresh_hw_device [current_hw_device]