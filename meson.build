project('tinc', ['c', 'cpp'],
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c89', 'werror=true'])

base_src = [
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

main_src = base_src + 'src/main.c'
exe = executable('tinc', main_src, install : true, dependencies : [llvm])
string_test = executable('tinc_test', base_src + 'test/string.c', install : true)
test('string test', string_test)
