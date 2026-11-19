#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "planets.h"

using lab4::PlanetList;
using lab4::SortKey;
using Names = std::vector<std::string>;

TEST(PlanetsTest, SortByDistance) {
    PlanetList list = lab4::create_planet_list();
    lab4::add_solar_system(list);
    EXPECT_EQ(lab4::planet_names(list, SortKey::kDistance),
              (Names{"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn",
                     "Uranus", "Neptune"}));
    lab4::destroy_planet_list(list);
}

TEST(PlanetsTest, SortByMass) {
    PlanetList list = lab4::create_planet_list();
    lab4::add_solar_system(list);
    EXPECT_EQ(lab4::planet_names(list, SortKey::kMass),
              (Names{"Mercury", "Mars", "Venus", "Earth", "Uranus", "Neptune",
                     "Saturn", "Jupiter"}));
    lab4::destroy_planet_list(list);
}

TEST(PlanetsTest, SortByDiameter) {
    PlanetList list = lab4::create_planet_list();
    lab4::add_solar_system(list);
    EXPECT_EQ(lab4::planet_names(list, SortKey::kDiameter),
              (Names{"Mercury", "Mars", "Venus", "Earth", "Neptune", "Uranus",
                     "Saturn", "Jupiter"}));
    lab4::destroy_planet_list(list);
}

TEST(PlanetsTest, EmptyList_NoNames) {
    PlanetList list = lab4::create_planet_list();
    EXPECT_TRUE(lab4::planet_names(list, SortKey::kMass).empty());
    lab4::destroy_planet_list(list);
}

TEST(PlanetsTest, InvalidPlanet_Throws) {
    EXPECT_THROW(lab4::create_planet("", 1.0, 1.0, 1.0), std::invalid_argument);
    EXPECT_THROW(lab4::create_planet("X", -1.0, 1.0, 1.0),
                 std::invalid_argument);
    PlanetList list = lab4::create_planet_list();
    EXPECT_THROW(lab4::add_planet_to_list(list, nullptr),
                 std::invalid_argument);
    lab4::destroy_planet_list(list);
}
