/**
 * @file menu.h
 * @brief Консольное меню программы и демонстрация заданий 1-11.
 * @author Жохова О. С.
 */
#ifndef MENU_H
#define MENU_H

#include <iosfwd>

namespace lab4 {

/**
 * @brief Чтение номера пункта меню.
 *
 * При вводе букв или числа вне диапазона выводит сообщение и просит
 * ввести снова.
 * @param in Поток ввода.
 * @param out Поток вывода (для подсказок).
 * @param min_value Наименьший допустимый номер.
 * @param max_value Наибольший допустимый номер.
 * @return int Введённый номер. Если ввод закончился (EOF), возвращает 0.
 */
int read_choice(std::istream& in, std::ostream& out, int min_value,
                int max_value);

/**
 * @brief Запуск демонстрации одного задания.
 * @param task Номер задания от 1 до 11.
 * @param in Поток ввода (нужен для задания 10).
 * @param out Поток вывода.
 * @exception std::invalid_argument Если номер задания вне диапазона.
 */
void run_task(int task, std::istream& in, std::ostream& out);

/**
 * @brief Главное меню: выводит список заданий и запускает выбранные,
 * пока пользователь не введёт 0.
 */
void run_menu(std::istream& in, std::ostream& out);

}  // namespace lab4

#endif  // MENU_H
