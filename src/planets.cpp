#include "planets.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>

namespace lab4 {

namespace {

// ссылка на поле next нужного потока
Planet*& next_of(Planet* planet, SortKey key) {
    switch (key) {
        case SortKey::kDistance:
            return planet->next_distance;
        case SortKey::kMass:
            return planet->next_mass;
        case SortKey::kDiameter:
            return planet->next_diameter;
    }
    throw std::invalid_argument("next_of: unknown key");
}

double key_of(const Planet* planet, SortKey key) {
    switch (key) {
        case SortKey::kDistance:
            return planet->distance_to_sun;
        case SortKey::kMass:
            return planet->mass;
        case SortKey::kDiameter:
            return planet->diameter;
    }
    throw std::invalid_argument("key_of: unknown key");
}

// вставка планеты в один поток отсортированного списка
void insert_into_thread(Planet* top, Planet* planet, SortKey key) {
    Planet* after_me = top;
    while (next_of(after_me, key) != nullptr &&
           key_of(next_of(after_me, key), key) < key_of(planet, key)) {
        after_me = next_of(after_me, key);
    }
    next_of(planet, key) = next_of(after_me, key);
    next_of(after_me, key) = planet;
}

void check_list(const PlanetList& list) {
    if (list.top == nullptr) {
        throw std::invalid_argument("planet list is not created");
    }
}

struct PlanetData {
    const char* name;
    double distance_to_sun;
    double mass;
    double diameter;
};

constexpr int kNameWidth = 10;
constexpr int kColumnWidth = 18;

// источник: NASA Planetary Fact Sheet
constexpr PlanetData kSolarSystem[] = {
    {"Earth", 149.6, 5.97, 12756},     {"Jupiter", 778.5, 1898.0, 142984},
    {"Mars", 228.0, 0.642, 6792},      {"Mercury", 57.9, 0.330, 4879},
    {"Neptune", 4515.0, 102.0, 49528}, {"Saturn", 1432.0, 568.0, 120536},
    {"Uranus", 2867.0, 86.8, 51118},   {"Venus", 108.2, 4.87, 12104},
};

}  // namespace

PlanetList create_planet_list() {
    PlanetList list;
    list.top = new Planet{"", 0.0, 0.0, 0.0, nullptr, nullptr, nullptr};
    return list;
}

Planet* create_planet(const std::string& name, double distance_to_sun,
                      double mass, double diameter) {
    if (name.empty()) {
        throw std::invalid_argument("create_planet: empty name");
    }
    if (distance_to_sun <= 0.0 || mass <= 0.0 || diameter <= 0.0) {
        throw std::invalid_argument("create_planet: values must be positive");
    }
    return new Planet{name,    distance_to_sun, mass,   diameter,
                      nullptr, nullptr,         nullptr};
}

void add_planet_to_list(PlanetList& list, Planet* planet) {
    check_list(list);
    if (planet == nullptr) {
        throw std::invalid_argument("add_planet_to_list: planet is nullptr");
    }
    insert_into_thread(list.top, planet, SortKey::kDistance);
    insert_into_thread(list.top, planet, SortKey::kMass);
    insert_into_thread(list.top, planet, SortKey::kDiameter);
}

void add_solar_system(PlanetList& list) {
    check_list(list);
    for (const PlanetData& data : kSolarSystem) {
        add_planet_to_list(list, create_planet(data.name, data.distance_to_sun,
                                               data.mass, data.diameter));
    }
}

std::vector<std::string> planet_names(const PlanetList& list, SortKey key) {
    check_list(list);
    std::vector<std::string> names;
    for (Planet* p = next_of(list.top, key); p != nullptr;
         p = next_of(p, key)) {
        names.push_back(p->name);
    }
    return names;
}

void print_planets(const PlanetList& list, SortKey key, std::ostream& out) {
    check_list(list);
    if (list.top->next_distance == nullptr) {
        out << "[empty]\n";
        return;
    }
    const std::ios_base::fmtflags old_flags = out.flags();
    const std::streamsize old_precision = out.precision();
    out << std::left << std::setw(kNameWidth) << "Planet" << std::right
        << std::setw(kColumnWidth) << "Distance, 1e6 km"
        << std::setw(kColumnWidth) << "Mass, 1e24 kg" << std::setw(kColumnWidth)
        << "Diameter, km" << '\n';
    out << std::fixed;
    for (Planet* p = next_of(list.top, key); p != nullptr;
         p = next_of(p, key)) {
        out << std::left << std::setw(kNameWidth) << p->name << std::right
            << std::setprecision(1) << std::setw(kColumnWidth)
            << p->distance_to_sun << std::setprecision(3)
            << std::setw(kColumnWidth) << p->mass << std::setprecision(0)
            << std::setw(kColumnWidth) << p->diameter << '\n';
    }
    out.flags(old_flags);
    out.precision(old_precision);
}

void destroy_planet_list(PlanetList& list) {
    // по потоку расстояний проходят все планеты, начиная с ограничителя
    Planet* planet = list.top;
    while (planet != nullptr) {
        Planet* next_planet = planet->next_distance;
        delete planet;
        planet = next_planet;
    }
    list.top = nullptr;
}

}  // namespace lab4
