#include "doubly_list.h"

#include <new>
#include <ostream>
#include <stdexcept>

namespace lab4 {

namespace {

void check_list(const DoublyList& list, const char* message) {
    if (list.top == nullptr || list.bottom == nullptr) {
        throw std::invalid_argument(message);
    }
}

bool is_sentinel(const DCell* cell) {
    return cell->prev == nullptr || cell->next == nullptr;
}

}  // namespace

DoublyList create_doubly_list() {
    DoublyList list;
    list.top = new DCell{kTopSentinelValue, nullptr, nullptr};
    try {
        list.bottom = new DCell{kBottomSentinelValue, nullptr, nullptr};
    } catch (const std::bad_alloc&) {
        delete list.top;
        throw;
    }
    list.top->next = list.bottom;
    list.bottom->prev = list.top;
    return list;
}

DCell* create_dcell(int value) {
    return new DCell{value, nullptr, nullptr};
}

void add_at_beginning(DoublyList& list, DCell* new_cell) {
    check_list(list, "add_at_beginning: list is not created");
    if (new_cell == nullptr) {
        throw std::invalid_argument("add_at_beginning: new_cell is nullptr");
    }
    new_cell->next = list.top->next;
    new_cell->prev = list.top;
    list.top->next->prev = new_cell;
    list.top->next = new_cell;
}

void add_at_end(DoublyList& list, DCell* new_cell) {
    check_list(list, "add_at_end: list is not created");
    if (new_cell == nullptr) {
        throw std::invalid_argument("add_at_end: new_cell is nullptr");
    }
    new_cell->next = list.bottom;
    new_cell->prev = list.bottom->prev;
    list.bottom->prev->next = new_cell;
    list.bottom->prev = new_cell;
}

void insert_cell(DCell* after_me, DCell* new_cell) {
    if (after_me == nullptr || new_cell == nullptr) {
        throw std::invalid_argument("insert_cell: nullptr argument");
    }
    if (after_me->next == nullptr) {
        throw std::invalid_argument("insert_cell: cannot insert after bottom");
    }
    new_cell->next = after_me->next;
    new_cell->prev = after_me;
    after_me->next->prev = new_cell;
    after_me->next = new_cell;
}

void add_at_beginning_via_insert(DoublyList& list, DCell* new_cell) {
    check_list(list, "add_at_beginning_via_insert: list is not created");
    insert_cell(list.top, new_cell);
}

void add_at_end_via_insert(DoublyList& list, DCell* new_cell) {
    check_list(list, "add_at_end_via_insert: list is not created");
    insert_cell(list.bottom->prev, new_cell);
}

void delete_cell(DCell* target) {
    if (target == nullptr) {
        throw std::invalid_argument("delete_cell: target is nullptr");
    }
    if (is_sentinel(target)) {
        throw std::invalid_argument("delete_cell: cannot delete sentinel");
    }
    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
}

DCell* find_sorted_from_top(const DoublyList& list, int target,
                            std::size_t& steps) {
    check_list(list, "find_sorted_from_top: list is not created");
    steps = 0;
    for (DCell* cell = list.top->next; cell != list.bottom; cell = cell->next) {
        ++steps;
        if (cell->value == target) {
            return cell;
        }
        if (cell->value > target) {
            return nullptr;  // дальше значения только больше
        }
    }
    return nullptr;
}

DCell* find_sorted_from_bottom(const DoublyList& list, int target,
                               std::size_t& steps) {
    check_list(list, "find_sorted_from_bottom: list is not created");
    steps = 0;
    for (DCell* cell = list.bottom->prev; cell != list.top; cell = cell->prev) {
        ++steps;
        if (cell->value == target) {
            return cell;
        }
        if (cell->value < target) {
            return nullptr;  // дальше значения только меньше
        }
    }
    return nullptr;
}

void insert_sorted(DoublyList& list, DCell* new_cell) {
    check_list(list, "insert_sorted: list is not created");
    if (new_cell == nullptr) {
        throw std::invalid_argument("insert_sorted: new_cell is nullptr");
    }
    DCell* after_me = list.top;
    while (after_me->next->value < new_cell->value) {
        after_me = after_me->next;
    }
    insert_cell(after_me, new_cell);
}

std::size_t count_dcells(const DoublyList& list) {
    check_list(list, "count_dcells: list is not created");
    std::size_t count = 0;
    for (DCell* cell = list.top->next; cell != list.bottom; cell = cell->next) {
        ++count;
    }
    return count;
}

void print_forward(const DoublyList& list, std::ostream& out) {
    check_list(list, "print_forward: list is not created");
    if (list.top->next == list.bottom) {
        out << "[empty]\n";
        return;
    }
    for (DCell* cell = list.top->next; cell != list.bottom; cell = cell->next) {
        out << cell->value;
        if (cell->next != list.bottom) {
            out << " <-> ";
        }
    }
    out << '\n';
}

void print_backward(const DoublyList& list, std::ostream& out) {
    check_list(list, "print_backward: list is not created");
    if (list.bottom->prev == list.top) {
        out << "[empty]\n";
        return;
    }
    for (DCell* cell = list.bottom->prev; cell != list.top; cell = cell->prev) {
        out << cell->value;
        if (cell->prev != list.top) {
            out << " <-> ";
        }
    }
    out << '\n';
}

void destroy_doubly_list(DoublyList& list) {
    DCell* cell = list.top;
    while (cell != nullptr) {
        DCell* next_cell = cell->next;
        delete cell;
        cell = next_cell;
    }
    list.top = nullptr;
    list.bottom = nullptr;
}

}  // namespace lab4
