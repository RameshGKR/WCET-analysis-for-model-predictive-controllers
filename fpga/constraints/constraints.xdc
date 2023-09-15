# Constraints file for Arty-A7-35 development board

## Configuration Banks Voltage Select
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]

## Clock signal
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports CLK]
create_clock -period 10.000 -name sys_clk_pin -waveform {0.000 5.000} -add [get_ports CLK]

## LEDs
set_property -dict {PACKAGE_PIN H5 IOSTANDARD LVCMOS33} [get_ports NOT_READY_LED]
set_property -dict {PACKAGE_PIN J5 IOSTANDARD LVCMOS33} [get_ports FORWARD_UART_ENABLED]
set_property -dict {PACKAGE_PIN T9 IOSTANDARD LVCMOS33} [get_ports INSTR_EN_LED]

## Reset button
set_property -dict {PACKAGE_PIN C2 IOSTANDARD LVCMOS33} [get_ports RST_N]

## USB-UART Interface
set_property -dict {PACKAGE_PIN D10 IOSTANDARD LVCMOS33} [get_ports UART_TX]
set_property -dict {PACKAGE_PIN A9 IOSTANDARD LVCMOS33} [get_ports UART_RX]

## Switches
set_property -dict {PACKAGE_PIN A8 IOSTANDARD LVCMOS33} [get_ports FORWARD_UART]

## ChipKit Outer Digital Header
set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[0]}]
set_property -dict {PACKAGE_PIN U16 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[1]}]
set_property -dict {PACKAGE_PIN P14 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[2]}]
set_property -dict {PACKAGE_PIN T11 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[3]}]
set_property -dict {PACKAGE_PIN R12 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[4]}]
set_property -dict {PACKAGE_PIN T14 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[5]}]
set_property -dict {PACKAGE_PIN T15 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[6]}]
set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[7]}]
set_property -dict {PACKAGE_PIN N15 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[8]}]
set_property -dict {PACKAGE_PIN M16 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[9]}]
set_property -dict {PACKAGE_PIN V17 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[10]}]
set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[11]}]
set_property -dict {PACKAGE_PIN R17 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[12]}]
set_property -dict {PACKAGE_PIN P17 IOSTANDARD LVCMOS33} [get_ports {INSTR_ID[13]}]

## ChipKit Inner Digital Header
set_property -dict {PACKAGE_PIN U11 IOSTANDARD LVCMOS33} [get_ports INSTR_EN]
set_property -dict {PACKAGE_PIN V16 IOSTANDARD LVCMOS33} [get_ports INSTR_RST]
set_property -dict {PACKAGE_PIN M13 IOSTANDARD LVCMOS33} [get_ports INSTR_DONE]
set_property -dict {PACKAGE_PIN R10 IOSTANDARD LVCMOS33} [get_ports INSTR_ACK]
set_property -dict {PACKAGE_PIN R11 IOSTANDARD LVCMOS33} [get_ports INSTR_ID_PARITY]

set_property -dict {PACKAGE_PIN P18 IOSTANDARD LVCMOS33} [get_ports UART_TX_F]
set_property -dict {PACKAGE_PIN N17 IOSTANDARD LVCMOS33} [get_ports UART_RX_F]





