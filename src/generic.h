#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "vector.h"

#include "string.h"
#include "token.h"

DECLARE_GENERIC_HASH(pp_token)
DECLARE_HASHMAP(string, pp_token)
DECLARE_HASHMAP(pp_token, pp_token)
DECLARE_VECTOR(pp_token)

#endif
