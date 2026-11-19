/**
 * @file cycle.h
 * @brief Обнаружение и разрыв цикла в списке: алгоритм черепахи и кролика
 * (задание 11).
 * @author Жохова О. С.
 */
#ifndef CYCLE_H
#define CYCLE_H

#include <cstddef>
#include <iosfwd>

#include "singly_list.h"

namespace lab4 {

/**
 * @brief Создание цикла: последняя ячейка начинает ссылаться на ячейку
 * с номером start_index (нумерация с 0).
 * @warning Пока цикл не разорван, destroy_list вызывать нельзя.
 * @exception std::invalid_argument Если список пустой или номер
 * больше номера последней ячейки.
 */
void make_cycle(ListWithBottom& list, std::size_t start_index);

/**
 * @brief Проверка, есть ли в списке цикл.
 * @param top Первая ячейка (может быть nullptr).
 * @note Время O(N), дополнительная память O(1).
 */
bool has_cycle(Cell* top);

/**
 * @brief Поиск ячейки, с которой начинается цикл.
 * @param top Первая ячейка.
 * @return Cell* Начало цикла или nullptr, если цикла нет.
 */
Cell* find_cycle_start(Cell* top);

/**
 * @brief Разрыв цикла: у последней ячейки цикла next становится nullptr.
 * @param top Первая ячейка.
 * @return true, если цикл был и он разорван, false, если цикла не было.
 */
bool break_cycle(Cell* top);

/**
 * @brief Вывод не более limit первых ячеек. Работает и для списка
 * с циклом, где обычный вывод был бы бесконечным.
 */
void print_first_cells(const Cell* top, std::size_t limit, std::ostream& out);

}  // namespace lab4

#endif  // CYCLE_H
