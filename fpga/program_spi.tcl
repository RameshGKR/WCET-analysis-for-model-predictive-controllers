# Constants
set deviceName xc7a35t_0
set memoryDevice s25fl128sxxxxxx0-spi-x1_x2_x4
set outputDir out

# Connect to hardware manager
open_hw_manager
connect_hw_server -allow_non_jtag

# Connect to target
open_hw_target
current_hw_device [get_hw_devices $deviceName]
refresh_hw_device -update_hw_probes false [current_hw_device]

# Create hardware memory configuration
create_hw_cfgmem -hw_device [current_hw_device] [lindex [get_cfgmem_parts $memoryDevice] 0]
set_property PROGRAM.BLANK_CHECK  0 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.ERASE  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.CFG_PROGRAM  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.VERIFY  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.CHECKSUM  0 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
refresh_hw_device [current_hw_device]

set_property PROGRAM.ADDRESS_RANGE  {use_file} [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.PRM_FILE {} [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.UNUSED_PIN_TERMINATION {pull-none} [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.BLANK_CHECK  0 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.ERASE  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.CFG_PROGRAM  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.VERIFY  1 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.CHECKSUM  0 [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]
set_property PROGRAM.FILES [list "$outputDir/top.bin" ] [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]

# Program memory configuration bitstream 
create_hw_bitstream -hw_device [current_hw_device] [get_property PROGRAM.HW_CFGMEM_BITFILE [current_hw_device]]
program_hw_devices [current_hw_device]
refresh_hw_device [current_hw_device]

# Program .bin to memory
program_hw_cfgmem -hw_cfgmem [ get_property PROGRAM.HW_CFGMEM [current_hw_device]]

# Disconnect
close_hw_manager