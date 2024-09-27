project('circles', 'c', version : '1.0')

project_sources = []
project_header_files = []

sdl2_dep = dependency('sdl2')

inc = [include_directories('include')]

subdir('src')
subdir('include')

exe = executable(
      'circles', 
      project_sources, 
      include_directories : inc,
      dependencies: sdl2_dep)

configure_file (input : '.clang-format',
               	output : '.clang-format',
	       				copy: true)
run_target('format',
  command : ['clang-format','-i','-style=file',project_sources, project_header_files])

