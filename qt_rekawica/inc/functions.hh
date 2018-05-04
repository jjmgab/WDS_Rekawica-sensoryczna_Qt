#include <QtGlobal>

/*!
 * \file Plik zawiera w sobie deklaracje dodatkowych funkcji.
 */

/*!
 * \brief Zwraca pseudolosowa wartosc z podanego zakresu
 * 
 * \param[in] Dolny zakres przedzialu
 * \param[in] Gorny zakres przedzialu
 * \param[out] Wartosc pseudolosowa
 */
int random_value(int range_min, int range_max);

/*!
 * \brief Generuje string z fragmentem koncowej ramki danych.
 * 
 * Potrzebne do debugowania parsera i wykresow.
 * \param[in] typ sensora
 * \param[in] id sensora
 * \param[in] wartosc odczytu sensora
 * \param[out] string z fragmentem ramki
 */
std::string generate_data(int sensor_type, int sensor_id, int sensor_value);