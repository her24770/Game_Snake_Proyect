#include "../../include/threads/TimerThread.hpp"
#include "../../include/utils/WindowsConsole.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <string>

std::string TimerThreadData::getFormattedTime() const {
    int totalMs = elapsedMilliseconds.load();
    int minutes = totalMs / 60000;
    int seconds = (totalMs % 60000) / 1000;
    int milliseconds = totalMs % 1000;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds << "."
        << std::setfill('0') << std::setw(3) << milliseconds;
    return oss.str();
}

void TimerThreadData::reset() {
    elapsedMilliseconds.store(0);
}

void* timerThreadFunction(void* arg) {
    TimerThreadData* timerData = static_cast<TimerThreadData*>(arg);
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    while (timerData->running.load()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
        
        timerData->elapsedMilliseconds.store(static_cast<int>(elapsed.count()));
        
        // Mostrar el tiempo en la esquina superior derecha
        std::string timeStr = timerData->getFormattedTime();
        
        // Posicionar en esquina superior derecha (fila 2, columna 70)
        std::cout << "\033[2;70H" << WindowsConsole::Colors::BRIGHT_YELLOW 
                  << "Tiempo: " << timeStr << WindowsConsole::Colors::RESET << std::flush;
        
        usleep(50000); // Actualizar cada 50ms para mejor precisión
    }
    
    return nullptr;
}