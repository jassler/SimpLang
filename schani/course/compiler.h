#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pools.h"

typedef struct {
	pool_t pool;
	FILE *file;
	int lookahead;
} context_t;

typedef enum {
	TOKEN_EOF,

	TOKEN_INTEGER,
	TOKEN_IDENT,

	TOKEN_LET,
	TOKEN_AND,
	TOKEN_IN,
	TOKEN_IF,
	TOKEN_THEN,
	TOKEN_ELSE,
	TOKEN_RECUR,
	TOKEN_LOOP,
	TOKEN_END,

	TOKEN_OPEN_PAREN,
	TOKEN_CLOSE_PAREN,
	TOKEN_NOT,
	TOKEN_LESS,
	TOKEN_PLUS,
	TOKEN_TIMES,
	TOKEN_NEGATE,

	TOKEN_LOGIC_AND,
	TOKEN_LOGIC_OR,

	TOKEN_ASSIGN,
	TOKEN_EQUALS,

	TOKEN_FIRST_KEYWORD = TOKEN_LET,
	TOKEN_LAST_KEYWORD = TOKEN_END,

	TOKEN_FIRST_OPERATOR = TOKEN_OPEN_PAREN,
	TOKEN_LAST_OPERATOR = TOKEN_EQUALS,

	TOKEN_FIRST_SINGLE_LETTER_OPERATOR = TOKEN_OPEN_PAREN,
	TOKEN_LAST_SINGLE_LETTER_OPERATOR = TOKEN_NEGATE
} token_type_t;

typedef struct {
	token_type_t type;
	union {
		int64_t i;
		char *name;
	} v;
} token_t;

bool scan_init (context_t *ctx, const char *filename);

token_t scan (context_t *ctx);

static inline bool
token_type_is_keyword (token_type_t t)
{
	return t >= TOKEN_FIRST_KEYWORD && t <= TOKEN_LAST_KEYWORD;
}

static inline bool
token_type_is_operator (token_type_t t)
{
	return t >= TOKEN_FIRST_OPERATOR && t <= TOKEN_LAST_OPERATOR;
}

const char* token_type_keyword_name (token_type_t t);
const char* token_type_operator_name (token_type_t t);

static inline void
error_assert (bool assertion, const char *error)
{
	if (assertion)
		return;
	fprintf(stderr, "Error: %s\n", error);
	exit(1);
}

#endif
