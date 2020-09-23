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

        void RemoveColor(Color color);

        void AddColor(Color color);

        void Advance();

        void Revert();

        bool HasActivePlayers() const;
    };
}  // namespace HokusBlokus::Blokus