#include "boundingRect.hpp"

namespace HokusBlokus::Blokus::Optimization {
	BoundingRect::BoundingRect() : minBounds(0, 0), maxBounds(0, 0) {
	}

	BoundingRect::BoundingRect(const Vec2i& minBounds, const Vec2i& maxBounds) : minBounds(minBounds), maxBounds(maxBounds) {
	}

	const Vec2i& BoundingRect::GetMinBounds() {
		return minBounds;
	}

	void BoundingRect::SetMinBounds(const Vec2i& minBounds) {
		this->minBounds = minBounds;
	}

	const Vec2i& BoundingRect::GetMaxBounds() {
		return maxBounds;
	}

	void BoundingRect::SetMaxBounds(const Vec2i& maxBounds) {
		this->maxBounds = maxBounds;
	}
}  // namespace HokusBlokus::Blokus::Optimization
