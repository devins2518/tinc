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
test_args = ['-O3']
string_test = executable('string_test', base_src + 'test/string.c', install : true, c_args : test_args)
hash_test = executable('hash_test', base_src + 'test/hash.c', install : true, c_args : test_args)
vector_test = executable('vector_test', base_src + 'test/vector.c', install : true, c_args : test_args)
test('string test', string_test)
test('hash test', hash_test)
test('vector test', vector_test)
