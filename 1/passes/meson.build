llvm_pass_sources = files('pass.cpp')

llvm_includedir = run_command(
    find_program('llvm-config'),
    '--includedir',
    check: true,
)
llvm_pass_includes = include_directories(llvm_includedir.stdout().strip())

libPass = shared_library(
    'Pass',
    llvm_pass_sources,
    override_options: 'b_lundef=false',
    include_directories: llvm_pass_includes,
)

project_sources += llvm_pass_sources
