#include "menu.h"

#include <initializer_list>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "cycle.h"
#include "doubly_list.h"
#include "planets.h"
#include "singly_list.h"

namespace lab4 {

namespace {

constexpr int kTaskCount = 11;

// ---------- вспомогательные функции вывода ----------

void print_state(const ListWithBottom& list, std::ostream& out) {
    print_list(list.top, out);
    out << "   top = ";
    if (list.top != nullptr) {
        out << list.top->value;
    } else {
        out << "null";
    }
    out << ", bottom = ";
    if (list.bottom != nullptr) {
        out << list.bottom->value;
    } else {
        out << "null";
    }
    out << '\n';
}

void print_both_ways(const DoublyList& list, std::ostream& out) {
    out << "   forward:  ";
    print_forward(list, out);
    out << "   backward: ";
    print_backward(list, out);
}

ListWithBottom make_list(std::initializer_list<int> values) {
    ListWithBottom list;
    for (int value : values) {
        add_at_end(list, create_cell(value));
    }
    return list;
}

// ---------- демонстрация заданий ----------

void demo_task1(std::ostream& out) {
    out << "Task 1. Singly linked list with bottom pointer\n";
    ListWithBottom list;
    add_at_end(list, create_cell(10));
    add_at_end(list, create_cell(20));
    add_at_end(list, create_cell(30));
    out << "add_at_end 10, 20, 30:     ";
    print_state(list, out);
    add_at_beginning(list, create_cell(5));
    out << "add_at_beginning 5:        ";
    print_state(list, out);
    delete_value(list, 30);
    out << "delete 30 (last cell):     ";
    print_state(list, out);
    add_at_end(list, create_cell(40));
    out << "add_at_end 40:             ";
    print_state(list, out);
    delete_value(list, 5);
    out << "delete 5 (first cell):     ";
    print_state(list, out);
    out << "delete 99: " << (delete_value(list, 99) ? "deleted" : "not found")
        << '\n';
    delete_value(list, 10);
    delete_value(list, 20);
    delete_value(list, 40);
    out << "delete 10, 20, 40:         ";
    print_state(list, out);
    destroy_list(list);
}

void demo_task2(std::ostream& out) {
    out << "Task 2. Max element of unsorted list\n";
    ListWithBottom list = make_list({7, -3, 15, 0, 15, 4});
    out << "list: ";
    print_list(list.top, out);
    out << "max = " << find_max(list.top) << '\n';
    destroy_list(list);
    out << "empty list: ";
    try {
        find_max(list.top);
    } catch (const std::invalid_argument& e) {
        out << "error: " << e.what() << '\n';
    }
}

void demo_task3(std::ostream& out) {
    out << "Task 3. Doubly linked list: add at beginning\n";
    DoublyList list = create_doubly_list();
    add_at_beginning(list, create_dcell(3));
    add_at_beginning(list, create_dcell(2));
    add_at_beginning(list, create_dcell(1));
    out << "add_at_beginning 3, 2, 1:\n";
    print_both_ways(list, out);
    destroy_doubly_list(list);
}

void demo_task4(std::ostream& out) {
    out << "Task 4. Doubly linked list: add at end\n";
    DoublyList list = create_doubly_list();
    add_at_end(list, create_dcell(1));
    add_at_end(list, create_dcell(2));
    add_at_end(list, create_dcell(3));
    out << "add_at_end 1, 2, 3:\n";
    print_both_ways(list, out);
    destroy_doubly_list(list);
}

void demo_task5(std::ostream& out) {
    out << "Task 5. Add at beginning and end via insert_cell\n";
    DoublyList list = create_doubly_list();
    add_at_beginning_via_insert(list, create_dcell(2));
    add_at_beginning_via_insert(list, create_dcell(1));
    add_at_end_via_insert(list, create_dcell(3));
    add_at_end_via_insert(list, create_dcell(4));
    out << "beginning 2, 1; end 3, 4:\n";
    print_both_ways(list, out);
    destroy_doubly_list(list);
}

void demo_task6(std::ostream& out) {
    out << "Task 6. Delete cell from doubly linked list\n";
    DoublyList list = create_doubly_list();
    for (int value = 1; value <= 5; ++value) {
        add_at_end(list, create_dcell(value));
    }
    out << "list:\n";
    print_both_ways(list, out);
    std::size_t steps = 0;
    delete_cell(find_sorted_from_top(list, 3, steps));
    delete_cell(list.top->next);
    delete_cell(list.bottom->prev);
    out << "delete 3 (middle), 1 (first), 5 (last):\n";
    print_both_ways(list, out);
    out << "delete top sentinel: ";
    try {
        delete_cell(list.top);
    } catch (const std::invalid_argument& e) {
        out << "error: " << e.what() << '\n';
    }
    destroy_doubly_list(list);
}

void demo_task7(std::ostream& out) {
    out << "Task 7. Search in sorted list from top and from bottom\n";
    DoublyList list = create_doubly_list();
    for (int value = 10; value <= 100; value += 10) {
        add_at_end(list, create_dcell(value));
    }
    out << "list: ";
    print_forward(list, out);
    for (int target : {20, 90, 55}) {
        std::size_t from_top = 0;
        std::size_t from_bottom = 0;
        const DCell* found = find_sorted_from_top(list, target, from_top);
        find_sorted_from_bottom(list, target, from_bottom);
        out << "find " << target << ": " << (found ? "found" : "not found")
            << ", steps from top = " << from_top
            << ", steps from bottom = " << from_bottom << '\n';
    }
    destroy_doubly_list(list);
}

void demo_task8(std::ostream& out) {
    out << "Task 8. Insert into sorted list with min/max sentinels\n";
    DoublyList list = create_doubly_list();
    for (int value : {50, 10, 30, 20, 40, 30, -5}) {
        insert_sorted(list, create_dcell(value));
    }
    out << "insert 50, 10, 30, 20, 40, 30, -5:\n";
    print_both_ways(list, out);
    destroy_doubly_list(list);
}

void demo_task9(std::ostream& out) {
    out << "Task 9. Is list sorted\n";
    ListWithBottom lists[] = {make_list({1, 2, 2, 5, 8}), make_list({1, 3, 2}),
                              make_list({42}), ListWithBottom{}};
    for (ListWithBottom& list : lists) {
        out << (is_sorted(list.top) ? "sorted:     " : "not sorted: ");
        print_list(list.top, out);
        destroy_list(list);
    }
}

void demo_task10(std::istream& in, std::ostream& out) {
    out << "Task 10. Multi-threaded list of planets\n";
    PlanetList list = create_planet_list();
    add_solar_system(list);
    while (true) {
        out << "Sort by: 1 - distance to Sun, 2 - mass, 3 - diameter, "
               "0 - back\n";
        const int choice = read_choice(in, out, 0, 3);
        if (choice == 0) {
            break;
        }
        const SortKey keys[] = {SortKey::kDistance, SortKey::kMass,
                                SortKey::kDiameter};
        print_planets(list, keys[choice - 1], out);
    }
    destroy_planet_list(list);
}

void demo_task11(std::ostream& out) {
    out << "Task 11. Tortoise and hare\n";
    ListWithBottom list = make_list({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    make_cycle(list, 4);
    out << "list with cycle (first 16 cells): ";
    print_first_cells(list.top, 16, out);
    out << "has cycle: " << (has_cycle(list.top) ? "yes" : "no") << '\n';
    out << "cycle starts at: " << find_cycle_start(list.top)->value << '\n';
    break_cycle(list.top);
    out << "after break_cycle: ";
    print_first_cells(list.top, 16, out);
    out << "has cycle: " << (has_cycle(list.top) ? "yes" : "no") << '\n';
    destroy_list(list);
}

void print_menu(std::ostream& out) {
    out << "Lab 4. Linked lists\n"
           " 1 - list with bottom: add and delete\n"
           " 2 - max element of list\n"
           " 3 - doubly list: add at beginning\n"
           " 4 - doubly list: add at end\n"
           " 5 - add via insert_cell\n"
           " 6 - doubly list: delete cell\n"
           " 7 - search from top and from bottom\n"
           " 8 - insert into sorted list\n"
           " 9 - is list sorted\n"
           "10 - planets (multi-threaded list)\n"
           "11 - tortoise and hare\n"
           " 0 - exit\n";
}

}  // namespace

int read_choice(std::istream& in, std::ostream& out, int min_value,
                int max_value) {
    std::string line;
    while (true) {
        out << "> ";
        if (!std::getline(in, line)) {
            out << '\n';
            return 0;  // ввод закончился
        }
        std::istringstream stream(line);
        int value = 0;
        char extra = 0;
        if (stream >> value && !(stream >> extra) && value >= min_value &&
            value <= max_value) {
            return value;
        }
        out << "Invalid input, enter a number from " << min_value << " to "
            << max_value << '\n';
    }
}

void run_task(int task, std::istream& in, std::ostream& out) {
    switch (task) {
        case 1:
            demo_task1(out);
            break;
        case 2:
            demo_task2(out);
            break;
        case 3:
            demo_task3(out);
            break;
        case 4:
            demo_task4(out);
            break;
        case 5:
            demo_task5(out);
            break;
        case 6:
            demo_task6(out);
            break;
        case 7:
            demo_task7(out);
            break;
        case 8:
            demo_task8(out);
            break;
        case 9:
            demo_task9(out);
            break;
        case 10:
            demo_task10(in, out);
            break;
        case 11:
            demo_task11(out);
            break;
        default:
            throw std::invalid_argument("run_task: unknown task number");
    }
}

void run_menu(std::istream& in, std::ostream& out) {
    print_menu(out);
    int choice = read_choice(in, out, 0, kTaskCount);
    while (choice != 0) {
        run_task(choice, in, out);
        out << '\n';
        choice = read_choice(in, out, 0, kTaskCount);
    }
}

}  // namespace lab4
