# Create project
create_project -part xc7a35ticsg324-1L -force proj 
set_property target_language VHDL [current_project]
set_property default_lib work [current_project]

# Get IP
read_ip ./ip/fifo_generator/fifo_generator.xci
read_ip ./ip/uart_clock_wiz/uart_clock_wiz.xci
upgrade_ip -quiet [get_ips *]
generate_target synthesis [get_ips *]

# Get HDL source
read_vhdl [glob ./hdl/*.vhd]

# Get constraints
read_xdc ./constraints/constraints.xdc

# Create output directory
set outputDir out
file mkdir $outputDir
set files [glob -nocomplain "$outputDir/*"]
if {[llength $files] != 0} {
    # Clear folder contents
    puts "Deleting contents of $outputDir..."
    file delete -force {*}[glob -directory $outputDir *]; 
} else {
    puts "$outputDir is empty."
}

# Synthesize
synth_ip -force [get_ips *]
synth_design -top top
write_checkpoint -force $outputDir/post_synth.dcp

# Place
opt_design
place_design
phys_opt_design
write_checkpoint -force $outputDir/post_place.dcp

# Route
route_design
write_checkpoint -force $outputDir/post_route.dcp

# Create bitstream and memory config file for SPI configuration
write_bitstream -verbose -force -bin_file $outputDir/top.bit

close_project