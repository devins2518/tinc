project('tinc', ['c', 'cpp'],
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c89', 'werror=true'])

base_src = [
  'src/main.c',
  'src/lexer.c',
  'src/scanner.c',
  'src/preprocessor.c',
  'src/compiler.c',
  'src/ast.c',
  'src/token.c',
  'src/string.c',
  'src/generic.c',
]

llvm = dependency('llvm')

exe = executable('tinc', base_src, install : true, dependencies : [llvm])

test('test_main', exe, args : 'src/test_main.c')
