#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#include "string.h"
#include "token.h"

typedef char *char_star;

DECLARE_HASHMAP(ident, char_star)

#endif
