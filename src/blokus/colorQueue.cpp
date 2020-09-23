#include "colorQueue.hpp"

namespace HokusBlokus::Blokus {
    ColorQueue::ColorQueue() {
        currentColor = Color::BLUE;
    }

    Color ColorQueue::GetCurrentColor() const {
        return currentColor;
    }

    void ColorQueue::RemoveColor(Color color) {
        removedColors.emplace(color);
    }

    void ColorQueue::AddColor(Color color) {
        removedColors.erase(color);
    }

    void ColorQueue::Advance() {
        do {
            currentColor = UIntToColor((ColorToUInt(currentColor) + 1) % 4);
        } while (removedColors.find(currentColor) != removedColors.end());
    }

    void ColorQueue::Revert() {
        do {
            currentColor = UIntToColor((ColorToUInt(currentColor) - 1) % 4);
        } while (removedColors.find(currentColor) != removedColors.end());
    }

    bool ColorQueue::HasActivePlayers() const {
        if(removedColors.size() < 4) {
            return true;
        }
        return false;
    }
}  // namespace HokusBlokus::Blokus