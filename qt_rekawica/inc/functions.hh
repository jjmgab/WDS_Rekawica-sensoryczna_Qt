#include <QtGlobal>
#include <string>

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

/*!
 * \brief Przelicza wartosci z zakresu wejsciowego na zakres wyjsciowy
 * \param[in] wartosc
 * \param[in] wejscie_minimalne
 * \param[in] wejscie_maksymalne
 * \param[in] wyjscie_minimalne
 * \param[in] wyjscie_maksymalne
 * \param[out] przeliczona wartosc na nowy zakres (double)
 */
double map(double x, double in_min, double in_max, double out_min, double out_max);