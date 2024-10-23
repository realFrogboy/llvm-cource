sdl2_dep = dependency('sdl2')

circles_sources = files('app.cpp', 'main.cpp', 'sim.cpp')
executable(
    'circles',
    circles_sources,
    include_directories: circles_includes,
    dependencies: sdl2_dep,
)

#clang++ main.cpp $FLAGS $LDFLAGS $LIBS -pthread -ltinfo -ldl

llvm_cxxflags = run_command(
    find_program('llvm-config'),
    '--cxxflags',
    check: true,
)
llvm_cxxflags = llvm_cxxflags.stdout().strip().split()

llvm_ldflags = run_command(
    find_program('llvm-config'),
    '--ldflags', '--libs',
    check: true,
)
llvm_ldflags = llvm_ldflags.stdout().strip().split() + ['-pthread', '-ltinfo', '-ldl', '-lz']

ir_creator_sources = files('sim.cpp', 'IRCreator.cpp')
executable(
    'ir_creator',
    ir_creator_sources,
    include_directories: circles_includes,
    dependencies: sdl2_dep,
    cpp_args:llvm_cxxflags + ['-g'],
    link_args:llvm_ldflags,
)

logger_sources = files('log.c')

project_sources += circles_sources + logger_sources + ir_creator_sources
