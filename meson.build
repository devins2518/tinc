project('tinc', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c89'])

base_src = [
  'src/main.c',
  'src/lexer.c',
  'src/scanner.c',
  'src/compiler.c',
  'src/token.c',
  'src/string.c',
  'src/vector.c',
]

exe = executable('tinc', base_src, install : true)

test('test_main', exe, args : 'src/test_main.c')
