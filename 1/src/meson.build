sdl2_dep = dependency('sdl2')

circles_sources = files('app.c', 'main.c', 'sim.c')
executable(
    'circles',
    circles_sources,
    include_directories: circles_includes,
    dependencies: sdl2_dep,
)

logger_sources = files('log.c')

project_sources += circles_sources + logger_sources
