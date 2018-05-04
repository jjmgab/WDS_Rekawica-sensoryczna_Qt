#include "functions.hh"

/*!
 * \brief Zwraca pseudolosowa wartosc z podanego zakresu
 * 
 * \param[in] Dolny zakres przedzialu
 * \param[in] Gorny zakres przedzialu
 * \param[out] Wartosc pseudolosowa
 */
int random_value(int range_min, int range_max) {
    qsrand(qrand());
    return qrand() % (((range_max + 1) - range_min) + range_min);
}

/*!
 * \brief Generuje string z fragmentem koncowej ramki danych.
 * 
 * Potrzebne do debugowania parsera i wykresow.
 * \param[in] typ sensora
 * \param[in] id sensora
 * \param[in] wartosc odczytu sensora
 * \param[out] string z fragmentem ramki
 */
std::string generate_data(int sensor_type, int sensor_id, int sensor_value) {
    char type[2];
    char id[2];
    char value[3];

    sprintf(type, "%01X", sensor_type);
    sprintf(id, "%01X", sensor_id);
    sprintf(value, "%02X", sensor_value);

    std::string t(type);
    std::string i(id);
    std::string v(value);

    return t + i + v;
}