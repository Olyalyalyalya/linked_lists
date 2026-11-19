/**
 * @file doubly_list.h
 * @brief Двунаправленный список с ограничителями (задания 3-8).
 * @author Жохова О. С.
 *
 * Список всегда содержит две служебные ячейки-ограничителя: top (в начале)
 * и bottom (в конце). В top хранится минимально возможное значение int,
 * в bottom максимально возможное. Данные лежат между ними.
 * Ошибки обрабатываются через исключения std::invalid_argument.
 */
#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <cstddef>
#include <iosfwd>
#include <limits>

namespace lab4 {

/// Значение верхнего ограничителя (меньше любого значения в списке).
inline constexpr int kTopSentinelValue = std::numeric_limits<int>::min();
/// Значение нижнего ограничителя (больше любого значения в списке).
inline constexpr int kBottomSentinelValue = std::numeric_limits<int>::max();

/// Ячейка двунаправленного списка.
struct DCell {
    int value;    ///< Значение ячейки.
    DCell* next;  ///< Следующая ячейка.
    DCell* prev;  ///< Предыдущая ячейка.
};

/// Двунаправленный список с верхним и нижним ограничителями.
struct DoublyList {
    DCell* top = nullptr;     ///< Верхний ограничитель.
    DCell* bottom = nullptr;  ///< Нижний ограничитель.
};

/**
 * @brief Создание пустого списка из двух ограничителей.
 * @return DoublyList Список, в котором top->next == bottom.
 */
DoublyList create_doubly_list();

/**
 * @brief Создание новой ячейки.
 * @param value Значение ячейки.
 * @return DCell* Ячейка с next == prev == nullptr.
 */
DCell* create_dcell(int value);

/**
 * @brief Добавление ячейки в начало списка, ссылки меняются напрямую
 * (задание 3).
 * @exception std::invalid_argument Если new_cell == nullptr
 * или список не создан.
 */
void add_at_beginning(DoublyList& list, DCell* new_cell);

/**
 * @brief Добавление ячейки в конец списка, ссылки меняются напрямую
 * (задание 4).
 * @exception std::invalid_argument Если new_cell == nullptr
 * или список не создан.
 */
void add_at_end(DoublyList& list, DCell* new_cell);

/**
 * @brief Вставка ячейки после заданной (InsertCell).
 * @param after_me Ячейка, после которой вставляется новая.
 * @param new_cell Новая ячейка.
 * @exception std::invalid_argument Если один из указателей nullptr
 * или after_me является нижним ограничителем.
 */
void insert_cell(DCell* after_me, DCell* new_cell);

/**
 * @brief Добавление в начало через insert_cell (задание 5).
 * @exception std::invalid_argument Как у insert_cell.
 */
void add_at_beginning_via_insert(DoublyList& list, DCell* new_cell);

/**
 * @brief Добавление в конец через insert_cell (задание 5).
 * @exception std::invalid_argument Как у insert_cell.
 */
void add_at_end_via_insert(DoublyList& list, DCell* new_cell);

/**
 * @brief Удаление заданной ячейки из списка (задание 6).
 * @param target Удаляемая ячейка. После вызова указатель недействителен.
 * @exception std::invalid_argument Если target == nullptr
 * или target является ограничителем.
 */
void delete_cell(DCell* target);

/**
 * @brief Поиск ячейки в отсортированном списке, начиная с верхнего
 * ограничителя (задание 7).
 * @param list Отсортированный список.
 * @param target Искомое значение.
 * @param steps Сюда записывается число просмотренных ячеек.
 * @return DCell* Найденная ячейка или nullptr.
 */
DCell* find_sorted_from_top(const DoublyList& list, int target,
                            std::size_t& steps);

/**
 * @brief Поиск ячейки в отсортированном списке, начиная с нижнего
 * ограничителя (задание 7).
 * @param list Отсортированный список.
 * @param target Искомое значение.
 * @param steps Сюда записывается число просмотренных ячеек.
 * @return DCell* Найденная ячейка или nullptr.
 */
DCell* find_sorted_from_bottom(const DoublyList& list, int target,
                               std::size_t& steps);

/**
 * @brief Вставка в отсортированный список с ограничителями min и max
 * (задание 8).
 *
 * Цикл поиска места не проверяет конец списка: его останавливает нижний
 * ограничитель, значение которого не меньше любого другого.
 * @exception std::invalid_argument Если new_cell == nullptr
 * или список не создан.
 * @note Время выполнения: O(N).
 */
void insert_sorted(DoublyList& list, DCell* new_cell);

/**
 * @brief Количество ячеек с данными (без ограничителей).
 */
std::size_t count_dcells(const DoublyList& list);

/**
 * @brief Вывод списка от начала к концу.
 * @param list Список. Для пустого списка печатается [empty].
 * @param out Поток вывода.
 */
void print_forward(const DoublyList& list, std::ostream& out);

/**
 * @brief Вывод списка от конца к началу (по ссылкам prev).
 * @param list Список. Для пустого списка печатается [empty].
 * @param out Поток вывода.
 */
void print_backward(const DoublyList& list, std::ostream& out);

/**
 * @brief Освобождение всех ячеек, включая ограничители.
 * @param list Список. После вызова top и bottom равны nullptr.
 */
void destroy_doubly_list(DoublyList& list);

}  // namespace lab4

#endif  // DOUBLY_LIST_H
