#include "cycle.h"

#include <ostream>
#include <stdexcept>

namespace lab4 {

namespace {

// Шаг 1-2: черепаха идёт на 1 ячейку, кролик на 2.
// Возвращает ячейку, где кролик догнал черепаху, или nullptr,
// если кролик дошёл до конца списка (цикла нет).
Cell* find_meeting_point(Cell* top) {
    Cell* tortoise = top;
    Cell* hare = top;
    while (hare != nullptr && hare->next != nullptr) {
        tortoise = tortoise->next;
        hare = hare->next->next;
        if (tortoise == hare) {
            return tortoise;
        }
    }
    return nullptr;
}

}  // namespace

void make_cycle(ListWithBottom& list, std::size_t start_index) {
    if (list.top == nullptr) {
        throw std::invalid_argument("make_cycle: empty list");
    }
    Cell* start = list.top;
    for (std::size_t i = 0; i < start_index; ++i) {
        start = start->next;
        if (start == nullptr) {
            throw std::invalid_argument("make_cycle: index out of range");
        }
    }
    list.bottom->next = start;
}

bool has_cycle(Cell* top) {
    return find_meeting_point(top) != nullptr;
}

Cell* find_cycle_start(Cell* top) {
    Cell* tortoise = find_meeting_point(top);
    if (tortoise == nullptr) {
        return nullptr;
    }
    // Шаг 3-4: кролик начинает сначала со скоростью 1,
    // новая встреча будет в начале цикла
    Cell* hare = top;
    while (hare != tortoise) {
        hare = hare->next;
        tortoise = tortoise->next;
    }
    return hare;
}

bool break_cycle(Cell* top) {
    Cell* hare = find_cycle_start(top);
    if (hare == nullptr) {
        return false;
    }
    // Шаг 5: кролик ждёт в начале цикла, черепаха проходит цикл,
    // пока её next не укажет на кролика
    Cell* tortoise = hare;
    while (tortoise->next != hare) {
        tortoise = tortoise->next;
    }
    // Шаг 6: разрыв цикла
    tortoise->next = nullptr;
    return true;
}

void print_first_cells(const Cell* top, std::size_t limit, std::ostream& out) {
    std::size_t printed = 0;
    for (; top != nullptr && printed < limit; top = top->next, ++printed) {
        if (printed > 0) {
            out << " -> ";
        }
        out << top->value;
    }
    if (top != nullptr) {
        out << " -> ...";
    }
    out << '\n';
}

}  // namespace lab4
