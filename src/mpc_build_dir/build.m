
        s_function_file_name_base = 'mpc_s_function_level2.c';
        c_file_name_base = 'mpc.c';
        casadi_codegen_file_name_base = 'mpc_codegen.c';
        [build_dir,~,~] = fileparts(mfilename('fullpath'));
        flags={['-I' build_dir] ['-L' build_dir] ['-I' casadi.GlobalOptions.getCasadiIncludePath()] ['-L' casadi.GlobalOptions.getCasadiPath()]};
        files = {[build_dir filesep s_function_file_name_base], [build_dir filesep c_file_name_base]};
        
          files=[files { [build_dir filesep casadi_codegen_file_name_base]}];
          flags=[flags {['-I' casadi.GlobalOptions.getCasadiIncludePath()] ['-I' casadi.GlobalOptions.getCasadiPath()] '-losqp'}];
          
      if ispc
      else
        flags=[flags {'-g' ['LDFLAGS="\$LDFLAGS -Wl,-rpath,' casadi.GlobalOptions.getCasadiPath() ' -Wl,-rpath,' build_dir '"']}];
      end
      mex(flags{:},files{:});
mex(flags{:}, [build_dir filesep 'integrate_mpc_s_function_level2.c']);
mex(flags{:}, [build_dir filesep 'dae_mpc_s_function_level2.c']);
mex(flags{:}, [build_dir filesep 'grid_mpc_s_function_level2.c']);
mex(flags{:}, [build_dir filesep 'cost_mpc_s_function_level2.c']);
