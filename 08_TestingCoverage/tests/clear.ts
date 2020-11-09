#include "buf.h"

#test clear
    float *a = 0;
    buf_clear(a);
    ck_assert_msg("clear empty", buf_size(a) == 0);
    ck_assert_msg("clear no-op", a == 0);