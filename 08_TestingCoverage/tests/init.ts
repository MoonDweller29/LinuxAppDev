#include "buf.h"

#test init
	float *a = 0;
    ck_assert_msg("capacity init", buf_capacity(a) == 0);
    ck_assert_msg("size init", buf_size(a) == 0);
    buf_push(a, 1.3f);
    ck_assert_msg("size 1", buf_size(a) == 1);
    ck_assert_msg("value", a[0] == (float)1.3f);
    buf_clear(a);
    ck_assert_msg("clear", buf_size(a) == 0);
    ck_assert_msg("clear not-free", a != 0);
    buf_free(a);
    ck_assert_msg("free", a == 0);