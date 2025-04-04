#include <gtest/gtest.h>

#include <tuple>

class WindowTest : public ::testing::TestWithParam<std::tuple<int, int, bool, bool>> {};