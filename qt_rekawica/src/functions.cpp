#include "functions.hh"

/*!
 * \brief Zwraca pseudolosowa wartosc z podanego zakresu
 * 
 * \param[in] Dolny zakres przedzialu
 * \param[in] Gorny zakres przedzialu
 * \param[out] Wartosc pseudolosowa
 */
int random_value(int range_min, int range_max) {
    //qsrand(qrand());
    //return qrand() % (((range_max + 1) - range_min) + range_min);
    return (rand() % (range_max+1) + range_min);
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

/*!
 * \brief Przelicza wartosci z zakresu wejsciowego na zakres wyjsciowy
 * \param[in] wartosc
 * \param[in] wejscie_minimalne
 * \param[in] wejscie_maksymalne
 * \param[in] wyjscie_minimalne
 * \param[in] wyjscie_maksymalne
 * \param[out] przeliczona wartosc na nowy zakres (double)
 */
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}