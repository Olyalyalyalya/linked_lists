/**
 * @file planets.h
 * @brief Многопотоковый список планет (задание 10).
 * @author Жохова О. С.
 *
 * Каждая планета хранится один раз, но входит сразу в три потока
 * (три цепочки ссылок): по расстоянию до Солнца, по массе и по диаметру.
 * Каждый поток отсортирован по возрастанию.
 */
#ifndef PLANETS_H
#define PLANETS_H

#include <iosfwd>
#include <string>
#include <vector>

namespace lab4 {

/// Планета. Поля next_* задают следующую планету в каждом потоке.
struct Planet {
    /// Название.
    std::string name;
    /// Среднее расстояние до Солнца, млн км.
    double distance_to_sun;
    /// Масса, 10^24 кг.
    double mass;
    /// Диаметр, км.
    double diameter;
    /// Следующая планета в потоке по расстоянию.
    Planet* next_distance;
    /// Следующая планета в потоке по массе.
    Planet* next_mass;
    /// Следующая планета в потоке по диаметру.
    Planet* next_diameter;
};

/// Поток, по которому выводится список.
enum class SortKey { kDistance, kMass, kDiameter };

/// Многопотоковый список. top - ограничитель, общий для всех потоков.
struct PlanetList {
    Planet* top = nullptr;  ///< Верхний ограничитель.
};

/**
 * @brief Создание пустого списка (только ограничитель).
 */
PlanetList create_planet_list();

/**
 * @brief Создание планеты.
 * @exception std::invalid_argument Если имя пустое или одно из чисел
 * не больше нуля.
 */
Planet* create_planet(const std::string& name, double distance_to_sun,
                      double mass, double diameter);

/**
 * @brief Добавление планеты сразу во все три потока с сохранением
 * сортировки (AddPlanetToList).
 * @exception std::invalid_argument Если planet == nullptr
 * или список не создан.
 * @note Время выполнения: O(N) для каждого потока.
 */
void add_planet_to_list(PlanetList& list, Planet* planet);

/**
 * @brief Добавление восьми планет Солнечной системы.
 *
 * Планеты добавляются по алфавиту, чтобы было видно, что порядок в потоках
 * задаёт сам список, а не порядок добавления.
 */
void add_solar_system(PlanetList& list);

/**
 * @brief Названия планет в порядке выбранного потока.
 * @exception std::invalid_argument Если список не создан.
 */
std::vector<std::string> planet_names(const PlanetList& list, SortKey key);

/**
 * @brief Вывод таблицы планет в порядке выбранного потока.
 * @exception std::invalid_argument Если список не создан.
 */
void print_planets(const PlanetList& list, SortKey key, std::ostream& out);

/**
 * @brief Освобождение всех планет и ограничителя.
 */
void destroy_planet_list(PlanetList& list);

}  // namespace lab4

#endif  // PLANETS_H
