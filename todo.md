- update parser.c to return ast_tokens with possible poisons (i.e. try_parse_type_specifier keyword but not type kw)
- fix memory leaks
- parser
    - audit parser
    - segregate index increment from commit
    - audit error message and parsing warning generation
    - hit 100% coverage
