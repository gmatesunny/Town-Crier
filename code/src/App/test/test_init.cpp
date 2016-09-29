//
// Created by fanz on 6/11/16.
//

#include "gtest/gtest.h"

#include "../Init.h"

TEST(BasicTest, Initialization) {
    sgx_enclave_id_t eid;
    int ret = initialize_enclave(ENCLAVE_FILENAME, &eid);
    EXPECT_EQ(0, ret);
}
