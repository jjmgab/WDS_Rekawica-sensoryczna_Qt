#include "time.hh"

/*!
 * \brief Funkcja wprowadzająca opóźnienie.
 * 
 * Wprowadza opóźnienie bez blokowania głównej pętli obsługi zdarzeń.
 * 
 * \param[in] Czas opóźnienia w sekundach
 */
void delay_seconds(const int& n)
{
    QTime waitTime = QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < waitTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}