// Chess
// Position.h
// Justyn Durnford
// Created on 2020-12-27
// Last updated on 2020-12-27
// Header file for the Position struct.

#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "Define.h"

struct Position
{
	uint8_t x, y;

	// Default constructor.
	Position() = default;

	// Copy constructor.
	Position(const Position& other) = default;

	// Move constructor.
	Position(Position&& other) = default;

	// 2 paramater constructor.
	// Sets x to new_x.
	// Sets y to new_y.
	Position(uint8_t new_x, uint8_t new_y);

	// Copy assignment operator.
	Position& operator = (const Position& other) = default;

	// Move assignment operator.
	Position& operator = (Position && other) = default;

	// Destructor.
	~Position();

	// Returns a std::string representation of the Position object.
	// Format: "{ x, y }".
	string toString() const;
};

// Creates a new Position with the given ints x and y.
Position make_position(uint8_t x, uint8_t y);

// Equality comparision operator.
// Returns true if:
//  - A.x == B.x AND
//  - A.y == B.y
bool operator == (const Position& A, const Position& B);

// Inequality comparision operator.
// Returns true if:
//  - A.x != B.x OR
//  - A.y != B.y
bool operator != (const Position& A, const Position& B);

#endif // POSITION_H_INCLUDED