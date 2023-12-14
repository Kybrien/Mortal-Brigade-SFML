#pragma once

#include "Component.h"

class SquareCollider : public Component
{
public:
	SquareCollider() = default;
	~SquareCollider() override = default;

	float width = 1.0f;
	float height = 1.0f;

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	void SetWidth(const float _width) { width = _width; }
	void SetHeight(const float _height) { height = _height; }

	void MoveBack(int _direction);

	void SetOldPosition(Maths::Vector2f _position) { old_position = _position; }
	Maths::Vector2f GetOldPosition() { return old_position; }
	float GetOldXPosition() { return old_position.x; }
	float GetOldYPosition() { return old_position.y; }

	static bool IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b);
	static bool WillCollide(const SquareCollider& _collider_a, Maths::Vector2f& _new_c_a_pos, const SquareCollider& _collider_b);

private:
	Maths::Vector2f old_position;
};
