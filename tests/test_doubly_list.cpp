#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "doubly_list.h"

using lab4::DCell;
using lab4::DoublyList;

namespace {

std::string forward(const DoublyList& list) {
    std::ostringstream out;
    lab4::print_forward(list, out);
    return out.str();
}

std::string backward(const DoublyList& list) {
    std::ostringstream out;
    lab4::print_backward(list, out);
    return out.str();
}

}  // namespace

TEST(DoublyListTest, Create_EmptyListHasTwoSentinels) {
    DoublyList list = lab4::create_doubly_list();
    EXPECT_EQ(list.top->next, list.bottom);
    EXPECT_EQ(list.bottom->prev, list.top);
    EXPECT_EQ(lab4::count_dcells(list), 0u);
    lab4::destroy_doubly_list(list);
}

// ---------- задания 3 и 4 ----------

TEST(DoublyListTest, AddAtBeginning_Order) {
    DoublyList list = lab4::create_doubly_list();
    lab4::add_at_beginning(list, lab4::create_dcell(2));
    lab4::add_at_beginning(list, lab4::create_dcell(1));
    EXPECT_EQ(forward(list), "1 <-> 2\n");
    EXPECT_EQ(backward(list), "2 <-> 1\n");
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, AddAtEnd_Order) {
    DoublyList list = lab4::create_doubly_list();
    lab4::add_at_end(list, lab4::create_dcell(1));
    lab4::add_at_end(list, lab4::create_dcell(2));
    EXPECT_EQ(forward(list), "1 <-> 2\n");
    EXPECT_EQ(backward(list), "2 <-> 1\n");
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, AddNullptrOrNotCreated_Throws) {
    DoublyList list = lab4::create_doubly_list();
    EXPECT_THROW(lab4::add_at_beginning(list, nullptr), std::invalid_argument);
    EXPECT_THROW(lab4::add_at_end(list, nullptr), std::invalid_argument);
    lab4::destroy_doubly_list(list);
    DoublyList not_created;
    DCell* cell = lab4::create_dcell(1);
    EXPECT_THROW(lab4::add_at_end(not_created, cell), std::invalid_argument);
    delete cell;
}

// ---------- задание 5 ----------

TEST(DoublyListTest, ViaInsert_SameResultAsDirect) {
    DoublyList list = lab4::create_doubly_list();
    lab4::add_at_beginning_via_insert(list, lab4::create_dcell(2));
    lab4::add_at_beginning_via_insert(list, lab4::create_dcell(1));
    lab4::add_at_end_via_insert(list, lab4::create_dcell(3));
    EXPECT_EQ(forward(list), "1 <-> 2 <-> 3\n");
    EXPECT_EQ(backward(list), "3 <-> 2 <-> 1\n");
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, InsertAfterBottom_Throws) {
    DoublyList list = lab4::create_doubly_list();
    DCell* cell = lab4::create_dcell(1);
    EXPECT_THROW(lab4::insert_cell(list.bottom, cell), std::invalid_argument);
    EXPECT_THROW(lab4::insert_cell(nullptr, cell), std::invalid_argument);
    delete cell;
    lab4::destroy_doubly_list(list);
}

// ---------- задание 6 ----------

TEST(DoublyListTest, DeleteCell_MiddleFirstLast) {
    DoublyList list = lab4::create_doubly_list();
    for (int value = 1; value <= 4; ++value) {
        lab4::add_at_end(list, lab4::create_dcell(value));
    }
    lab4::delete_cell(list.top->next->next);  // 2
    lab4::delete_cell(list.top->next);        // 1
    lab4::delete_cell(list.bottom->prev);     // 4
    EXPECT_EQ(forward(list), "3\n");
    lab4::delete_cell(list.top->next);
    EXPECT_EQ(forward(list), "[empty]\n");
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, DeleteSentinelOrNullptr_Throws) {
    DoublyList list = lab4::create_doubly_list();
    EXPECT_THROW(lab4::delete_cell(list.top), std::invalid_argument);
    EXPECT_THROW(lab4::delete_cell(list.bottom), std::invalid_argument);
    EXPECT_THROW(lab4::delete_cell(nullptr), std::invalid_argument);
    lab4::destroy_doubly_list(list);
}

// ---------- задание 7 ----------

TEST(DoublyListTest, SearchFromTopAndBottom_Steps) {
    DoublyList list = lab4::create_doubly_list();
    for (int value = 10; value <= 100; value += 10) {
        lab4::add_at_end(list, lab4::create_dcell(value));
    }
    std::size_t steps = 0;
    EXPECT_NE(lab4::find_sorted_from_top(list, 20, steps), nullptr);
    EXPECT_EQ(steps, 2u);
    EXPECT_NE(lab4::find_sorted_from_bottom(list, 20, steps), nullptr);
    EXPECT_EQ(steps, 9u);
    EXPECT_EQ(lab4::find_sorted_from_top(list, 55, steps), nullptr);
    EXPECT_EQ(steps, 6u);
    EXPECT_EQ(lab4::find_sorted_from_bottom(list, 55, steps), nullptr);
    EXPECT_EQ(steps, 6u);
    lab4::destroy_doubly_list(list);
}

// ---------- задание 8 ----------

TEST(DoublyListTest, InsertSorted_KeepsOrder) {
    DoublyList list = lab4::create_doubly_list();
    for (int value : {50, 10, 30, 20, 30, -5}) {
        lab4::insert_sorted(list, lab4::create_dcell(value));
    }
    EXPECT_EQ(forward(list), "-5 <-> 10 <-> 20 <-> 30 <-> 30 <-> 50\n");
    EXPECT_EQ(backward(list), "50 <-> 30 <-> 30 <-> 20 <-> 10 <-> -5\n");
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, InsertSorted_ExtremeValues) {
    DoublyList list = lab4::create_doubly_list();
    lab4::insert_sorted(list, lab4::create_dcell(lab4::kBottomSentinelValue));
    lab4::insert_sorted(list, lab4::create_dcell(0));
    lab4::insert_sorted(list, lab4::create_dcell(lab4::kTopSentinelValue));
    EXPECT_EQ(list.top->next->value, lab4::kTopSentinelValue);
    EXPECT_EQ(list.bottom->prev->value, lab4::kBottomSentinelValue);
    EXPECT_EQ(lab4::count_dcells(list), 3u);
    lab4::destroy_doubly_list(list);
}

TEST(DoublyListTest, InsertSorted_Nullptr_Throws) {
    DoublyList list = lab4::create_doubly_list();
    EXPECT_THROW(lab4::insert_sorted(list, nullptr), std::invalid_argument);
    lab4::destroy_doubly_list(list);
}
