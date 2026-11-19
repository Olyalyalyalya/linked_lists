#include "singly_list.h"

#include <ostream>
#include <stdexcept>

namespace lab4 {

Cell* create_cell(int value) {
    return new Cell{value, nullptr};
}

void add_at_end(ListWithBottom& list, Cell* new_cell) {
    if (new_cell == nullptr) {
        throw std::invalid_argument("add_at_end: new_cell is nullptr");
    }
    new_cell->next = nullptr;
    if (list.top == nullptr) {
        list.top = new_cell;
        list.bottom = new_cell;
    } else {
        list.bottom->next = new_cell;
        list.bottom = new_cell;
    }
}

void add_at_beginning(ListWithBottom& list, Cell* new_cell) {
    if (new_cell == nullptr) {
        throw std::invalid_argument("add_at_beginning: new_cell is nullptr");
    }
    new_cell->next = list.top;
    list.top = new_cell;
    // в пустом списке новая ячейка одновременно и первая, и последняя
    if (list.bottom == nullptr) {
        list.bottom = new_cell;
    }
}

Cell* find_cell(const ListWithBottom& list, int target) {
    for (Cell* cell = list.top; cell != nullptr; cell = cell->next) {
        if (cell->value == target) {
            return cell;
        }
    }
    return nullptr;
}

bool delete_value(ListWithBottom& list, int target) {
    if (list.top == nullptr) {
        return false;
    }
    // удаление первой ячейки
    if (list.top->value == target) {
        Cell* target_cell = list.top;
        list.top = target_cell->next;
        if (list.bottom == target_cell) {
            list.bottom = nullptr;  // это была единственная ячейка
        }
        delete target_cell;
        return true;
    }
    // ищем ячейку перед удаляемой
    Cell* prev = list.top;
    while (prev->next != nullptr) {
        if (prev->next->value == target) {
            Cell* target_cell = prev->next;
            prev->next = target_cell->next;
            if (list.bottom == target_cell) {
                list.bottom = prev;  // удалили последнюю ячейку
            }
            delete target_cell;
            return true;
        }
        prev = prev->next;
    }
    return false;
}

std::size_t count_cells(const Cell* top) {
    std::size_t count = 0;
    for (; top != nullptr; top = top->next) {
        ++count;
    }
    return count;
}

int find_max(const Cell* top) {
    if (top == nullptr) {
        throw std::invalid_argument("find_max: empty list");
    }
    int max_value = top->value;
    for (const Cell* cell = top->next; cell != nullptr; cell = cell->next) {
        if (cell->value > max_value) {
            max_value = cell->value;
        }
    }
    return max_value;
}

bool is_sorted(const Cell* top) {
    while (top != nullptr && top->next != nullptr) {
        if (top->value > top->next->value) {
            return false;
        }
        top = top->next;
    }
    return true;
}

void print_list(const Cell* top, std::ostream& out) {
    if (top == nullptr) {
        out << "[empty]\n";
        return;
    }
    for (; top != nullptr; top = top->next) {
        out << top->value;
        if (top->next != nullptr) {
            out << " -> ";
        }
    }
    out << '\n';
}

void destroy_list(ListWithBottom& list) {
    Cell* cell = list.top;
    while (cell != nullptr) {
        Cell* next_cell = cell->next;
        delete cell;
        cell = next_cell;
    }
    list.top = nullptr;
    list.bottom = nullptr;
}

}  // namespace lab4
