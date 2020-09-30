#pragma once

#include <set>
#include <algorithm>

#include "color.hpp"

namespace HokusBlokus::Blokus {
    class ColorQueue {
        Color currentColor;
        std::set<Color> removedColors;

    public:
        ColorQueue();

        Color GetCurrentColor() const;

        void SetCurrentColor(Color color);

        void RemoveColor(Color color);

        void AddColor(Color color);

        void Advance();

        void Revert();

        bool HasActivePlayers() const;

        bool WasColorRemoved(Color color) const;
    };
}  // namespace HokusBlokus::Blokus