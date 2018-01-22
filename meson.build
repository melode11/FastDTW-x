project('fastdtw', 'cpp', license : 'MIT')

inc_priv = include_directories('include/fastdtw')
inc = include_directories('include')

subdir('include/fastdtw')
subdir('source')

dep = declare_dependency(link_with : lib, include_directories : inc)

