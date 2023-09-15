var scriptsDir = RCI.ric.get_value("//scripts-folder");

// make run: start gdb to load and execute program on target over serial
// start is used to run gdb in a separate process
// -o main.elf prevents recompilation
var rpiComPort = getEnvironment("RPI_COM_PORT");
var cmdArgs = ["start", "\"Deploy\"", "make", "-o", "main.elf", "run", "COM=" + rpiComPort];
print("Loading and executing program: " + cmdArgs);
shell_call(cmdArgs);

// Launch Python script to collect trace from serial port
var fpgaComPort = getEnvironment("FPGA_COM_PORT");
var tracefile = getEnvironment("TRACE_FILE");
var cmdArgs = ["start", "\"Log\"", "/WAIT", "python", scriptsDir+"get_trace.py", fpgaComPort, tracefile];
print("Receive timestamps: " + cmdArgs);
shell_call(cmdArgs);

