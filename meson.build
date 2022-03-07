project('src', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])


base_src = run_command('find', 'src', '-name', '*.c', check: true).stdout().strip()

exe = executable('src', base_src, install : true)

test('test', exe)
