#include <gtest/gtest.h>

#include <initializer_list>
#include <stdexcept>

#include "singly_list.h"

using lab4::Cell;
using lab4::ListWithBottom;

namespace {

ListWithBottom make_list(std::initializer_list<int> values) {
    ListWithBottom list;
    for (int value : values) {
        lab4::add_at_end(list, lab4::create_cell(value));
    }
    return list;
}

}  // namespace

// ---------- задание 1: список с bottom ----------

TEST(SinglyListTest, AddAtEnd_UpdatesBottom) {
    ListWithBottom list = make_list({1, 2, 3});
    EXPECT_EQ(list.top->value, 1);
    EXPECT_EQ(list.bottom->value, 3);
    EXPECT_EQ(list.bottom->next, nullptr);
    EXPECT_EQ(lab4::count_cells(list.top), 3u);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, AddAtBeginning_EmptyListSetsBottom) {
    ListWithBottom list;
    lab4::add_at_beginning(list, lab4::create_cell(7));
    EXPECT_EQ(list.top, list.bottom);
    EXPECT_EQ(list.bottom->value, 7);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, DeleteLast_MovesBottomBack) {
    ListWithBottom list = make_list({1, 2, 3});
    EXPECT_TRUE(lab4::delete_value(list, 3));
    EXPECT_EQ(list.bottom->value, 2);
    lab4::add_at_end(list, lab4::create_cell(4));
    EXPECT_EQ(list.top->next->next->value, 4);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, DeleteFirst_MovesTop) {
    ListWithBottom list = make_list({1, 2, 3});
    EXPECT_TRUE(lab4::delete_value(list, 1));
    EXPECT_EQ(list.top->value, 2);
    EXPECT_EQ(list.bottom->value, 3);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, DeleteOnlyCell_ClearsTopAndBottom) {
    ListWithBottom list = make_list({5});
    EXPECT_TRUE(lab4::delete_value(list, 5));
    EXPECT_EQ(list.top, nullptr);
    EXPECT_EQ(list.bottom, nullptr);
}

TEST(SinglyListTest, DeleteMissingValue_ReturnsFalse) {
    ListWithBottom list = make_list({1, 2});
    EXPECT_FALSE(lab4::delete_value(list, 9));
    EXPECT_EQ(lab4::count_cells(list.top), 2u);
    ListWithBottom empty;
    EXPECT_FALSE(lab4::delete_value(empty, 1));
    lab4::destroy_list(list);
}

TEST(SinglyListTest, AddNullptr_Throws) {
    ListWithBottom list;
    EXPECT_THROW(lab4::add_at_end(list, nullptr), std::invalid_argument);
    EXPECT_THROW(lab4::add_at_beginning(list, nullptr), std::invalid_argument);
}

// ---------- задание 2: максимум ----------

TEST(SinglyListTest, FindMax_NormalCase) {
    ListWithBottom list = make_list({7, -3, 15, 0, 4});
    EXPECT_EQ(lab4::find_max(list.top), 15);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, FindMax_AllNegative) {
    ListWithBottom list = make_list({-8, -2, -5});
    EXPECT_EQ(lab4::find_max(list.top), -2);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, FindMax_SingleCell) {
    ListWithBottom list = make_list({42});
    EXPECT_EQ(lab4::find_max(list.top), 42);
    lab4::destroy_list(list);
}

TEST(SinglyListTest, FindMax_EmptyList_Throws) {
    EXPECT_THROW(lab4::find_max(nullptr), std::invalid_argument);
}

// ---------- задание 9: проверка сортировки ----------

TEST(SinglyListTest, IsSorted_SortedWithDuplicates) {
    ListWithBottom list = make_list({1, 2, 2, 5});
    EXPECT_TRUE(lab4::is_sorted(list.top));
    lab4::destroy_list(list);
}

TEST(SinglyListTest, IsSorted_NotSorted) {
    ListWithBottom list = make_list({1, 3, 2});
    EXPECT_FALSE(lab4::is_sorted(list.top));
    lab4::destroy_list(list);
}

TEST(SinglyListTest, IsSorted_EmptyAndSingle) {
    EXPECT_TRUE(lab4::is_sorted(nullptr));
    ListWithBottom list = make_list({4});
    EXPECT_TRUE(lab4::is_sorted(list.top));
    lab4::destroy_list(list);
}
