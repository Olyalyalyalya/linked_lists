#include <gtest/gtest.h>

#include <stdexcept>

#include "cycle.h"

using lab4::ListWithBottom;

namespace {

ListWithBottom make_list(int count) {
    ListWithBottom list;
    for (int value = 0; value < count; ++value) {
        lab4::add_at_end(list, lab4::create_cell(value));
    }
    return list;
}

}  // namespace

TEST(CycleTest, NoCycle) {
    ListWithBottom list = make_list(5);
    EXPECT_FALSE(lab4::has_cycle(list.top));
    EXPECT_EQ(lab4::find_cycle_start(list.top), nullptr);
    EXPECT_FALSE(lab4::break_cycle(list.top));
    lab4::destroy_list(list);
}

TEST(CycleTest, EmptyList) {
    EXPECT_FALSE(lab4::has_cycle(nullptr));
    EXPECT_FALSE(lab4::break_cycle(nullptr));
}

TEST(CycleTest, FindStartAndBreak) {
    ListWithBottom list = make_list(10);
    lab4::make_cycle(list, 4);
    EXPECT_TRUE(lab4::has_cycle(list.top));
    EXPECT_EQ(lab4::find_cycle_start(list.top)->value, 4);
    EXPECT_TRUE(lab4::break_cycle(list.top));
    EXPECT_FALSE(lab4::has_cycle(list.top));
    EXPECT_EQ(list.bottom->next, nullptr);
    EXPECT_EQ(lab4::count_cells(list.top), 10u);
    lab4::destroy_list(list);
}

TEST(CycleTest, WholeListIsCycle) {
    ListWithBottom list = make_list(6);
    lab4::make_cycle(list, 0);
    EXPECT_EQ(lab4::find_cycle_start(list.top), list.top);
    EXPECT_TRUE(lab4::break_cycle(list.top));
    EXPECT_EQ(lab4::count_cells(list.top), 6u);
    lab4::destroy_list(list);
}

TEST(CycleTest, SingleCellPointsToItself) {
    ListWithBottom list = make_list(1);
    lab4::make_cycle(list, 0);
    EXPECT_TRUE(lab4::has_cycle(list.top));
    EXPECT_TRUE(lab4::break_cycle(list.top));
    EXPECT_EQ(list.top->next, nullptr);
    lab4::destroy_list(list);
}

TEST(CycleTest, MakeCycle_BadIndex_Throws) {
    ListWithBottom list = make_list(3);
    EXPECT_THROW(lab4::make_cycle(list, 3), std::invalid_argument);
    ListWithBottom empty;
    EXPECT_THROW(lab4::make_cycle(empty, 0), std::invalid_argument);
    lab4::destroy_list(list);
}
