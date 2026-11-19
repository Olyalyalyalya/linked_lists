/**
 * @file singly_list.h
 * @brief Однонаправленный список с указателем bottom (задания 1, 2, 9).
 * @author Жохова О. С.
 *
 * Ошибки обрабатываются через исключения std::invalid_argument.
 */
#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <cstddef>
#include <iosfwd>

namespace lab4 {

/// Ячейка однонаправленного списка.
struct Cell {
    int value;   ///< Значение ячейки.
    Cell* next;  ///< Следующая ячейка или nullptr.
};

/// Однонаправленный список с указателями на первую и последнюю ячейки.
struct ListWithBottom {
    Cell* top = nullptr;     ///< Первая ячейка.
    Cell* bottom = nullptr;  ///< Последняя ячейка.
};

/**
 * @brief Создание новой ячейки.
 * @param value Значение ячейки.
 * @return Cell* Ячейка с next == nullptr. Освобождается вместе со списком.
 */
Cell* create_cell(int value);

/**
 * @brief Добавление ячейки в конец списка за O(1) (задание 1).
 * @param list Список.
 * @param new_cell Добавляемая ячейка.
 * @exception std::invalid_argument Если new_cell == nullptr.
 */
void add_at_end(ListWithBottom& list, Cell* new_cell);

/**
 * @brief Добавление ячейки в начало списка.
 *
 * Если список был пустым, bottom тоже указывает на новую ячейку.
 * @param list Список.
 * @param new_cell Добавляемая ячейка.
 * @exception std::invalid_argument Если new_cell == nullptr.
 */
void add_at_beginning(ListWithBottom& list, Cell* new_cell);

/**
 * @brief Поиск первой ячейки с заданным значением.
 * @param list Список.
 * @param target Искомое значение.
 * @return Cell* Найденная ячейка или nullptr.
 */
Cell* find_cell(const ListWithBottom& list, int target);

/**
 * @brief Удаление первой ячейки с заданным значением (задание 1).
 *
 * Если удаляется последняя ячейка, bottom переносится на предыдущую.
 * Если удаляется единственная ячейка, top и bottom становятся nullptr.
 * @param list Список.
 * @param target Значение удаляемой ячейки.
 * @return true, если ячейка найдена и удалена, иначе false.
 */
bool delete_value(ListWithBottom& list, int target);

/**
 * @brief Количество ячеек в списке.
 * @param top Первая ячейка (может быть nullptr).
 * @return std::size_t Число ячеек.
 */
std::size_t count_cells(const Cell* top);

/**
 * @brief Поиск наибольшего значения в несортированном списке (задание 2).
 * @param top Первая ячейка.
 * @return int Наибольшее значение.
 * @exception std::invalid_argument Если список пустой (top == nullptr).
 * @note Время выполнения: O(N).
 */
int find_max(const Cell* top);

/**
 * @brief Проверка, отсортирован ли список по неубыванию (задание 9).
 * @param top Первая ячейка.
 * @return true для пустого списка, списка из одной ячейки и
 * отсортированного списка, иначе false.
 */
bool is_sorted(const Cell* top);

/**
 * @brief Вывод списка в виде 1 -> 2 -> 3.
 * @param top Первая ячейка. Для пустого списка печатается [empty].
 * @param out Поток вывода.
 */
void print_list(const Cell* top, std::ostream& out);

/**
 * @brief Освобождение всех ячеек списка.
 * @param list Список. После вызова top и bottom равны nullptr.
 */
void destroy_list(ListWithBottom& list);

}  // namespace lab4

#endif  // SINGLY_LIST_H
