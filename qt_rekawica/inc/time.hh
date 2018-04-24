#include <QCoreApplication>
#include <QTime>

/*!
 * \brief Funkcja wprowadzająca opóźnienie.
 * 
 * Wprowadza opóźnienie bez blokowania głównej pętli obsługi zdarzeń.
 * 
 * \param[in] Czas opóźnienia w sekundach
 */
void delay_seconds(const int&);