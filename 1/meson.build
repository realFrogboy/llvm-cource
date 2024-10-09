project('circles', 'c', 'cpp', version: '1.0')

fs = import('fs')

compiler = meson.get_compiler('c')
if compiler.get_id() != 'clang'
    error('clang required')
endif
compiler = meson.get_compiler('cpp')
if compiler.get_id() != 'clang'
    error('clang++ required')
endif

project_sources = []
project_headers = []

subdir('passes')
subdir('include')
subdir('src')

configure_file(input: '.clang-format', output: '.clang-format', copy: true)
run_target(
    'format',
    command: [
        'clang-format',
        '-i',
        '-style=file',
        project_sources,
        project_headers,
    ],
)
