#include "buf.h"

#test pop
	long *ai = 0;
	buf_grow(ai, 1000);
    ck_assert_msg("grow 1000", buf_capacity(ai) == 1000);
    ck_assert_msg("size 0 (grow)", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    ck_assert_msg("trunc 100", buf_capacity(ai) == 100);
    buf_free(ai);