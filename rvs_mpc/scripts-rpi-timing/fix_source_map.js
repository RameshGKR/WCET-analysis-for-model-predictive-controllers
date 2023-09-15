var scriptsDir = RCI.ric.get_value("//scripts-folder");
var prepResult = RCI.ric.get_value("//rvsconfig//integrations//integration[@integration-name='rpi-timing']//preparation-report-file");
var cmdArgs = ["rciscript", scriptsDir+"fix_source_map.py", "--arg", prepResult];
shell_call(cmdArgs);