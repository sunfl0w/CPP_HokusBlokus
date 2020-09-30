#include "colorQueue.hpp"

namespace HokusBlokus::Blokus {
    ColorQueue::ColorQueue() {
        currentColor = Color::BLUE;
    }

    Color ColorQueue::GetCurrentColor() const {
        return currentColor;
    }

    void ColorQueue::SetCurrentColor(Color color) {
        currentColor = color;
    }

    void ColorQueue::RemoveColor(Color color) {
        removedColors.emplace(color);
    }

    void ColorQueue::AddColor(Color color) {
        removedColors.erase(color);
    }

    void ColorQueue::Advance() {
        if (removedColors.size() < 4) {
            do {
                currentColor = IntToColor((ColorToInt(currentColor) + 1) % 4);
            } while (removedColors.find(currentColor) != removedColors.end());
        }
    }

    void ColorQueue::Revert() {
        do {
            currentColor = IntToColor((ColorToInt(currentColor) - 1) % 4);
        } while (removedColors.find(currentColor) != removedColors.end());
    }

    bool ColorQueue::HasActivePlayers() const {
        if (removedColors.size() < 4) {
            return true;
        }
        return false;
    }

    bool ColorQueue::WasColorRemoved(Color color) const {
        return removedColors.find(color) != removedColors.end();
    }
}  // namespace HokusBlokus::Blokus