#include "generic.h"

IMPL_GENERIC_HASH(pp_token)
IMPL_HASHMAP(string, pp_token, string_hash, string_eq)
IMPL_HASHMAP(pp_token, pp_token, pp_token_hash, pp_token_eq)
IMPL_VECTOR(pp_token)
