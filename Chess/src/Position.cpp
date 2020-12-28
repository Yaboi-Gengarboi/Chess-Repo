// Chess
// Position.cpp
// Justyn Durnford
// Created on 2020-12-27
// Last updated on 2020-12-27
// Source file for the Position struct.

#include "Position.h"

Position::Position(uint8_t new_x, uint8_t new_y)
	: x(new_x), y(new_y) {}

string Position::toString() const
{
	string str = "{ " + to_string(x) + ", " + to_string(y) + " }";
	return str;
}

Position make_position(uint8_t x, uint8_t y)
{
	return Position(x, y);
}

bool operator == (const Position& A, const Position& B)
{
	if (A.x != B.x)
		return false;

	if (A.y != B.y)
		return false;

	return true;
}

bool operator != (const Position& A, const Position& B)
{
	if (A.x != B.x)
		return true;

	if (A.y != B.y)
		return true;

	return false;
}