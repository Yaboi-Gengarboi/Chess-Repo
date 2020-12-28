// Chess
// Piece.h
// Justyn Durnford
// Created on 2020-12-27
// Last updated on 2020-12-27
// Header file for the Piece class.

#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "Define.h"
#include "Graphics.h"

#include "Position.h"

class Piece
{
	const int8_t id_;
	const string name_;
	Position pos_;
	const Sprite sprite_;

	public:

	// Default constructor.
	Piece() = default;

	// Copy constructor.
	Piece(const Piece& other) = default;

	// Move constructor.
	Piece(Piece&& other) = default;

	// 4-parameter constructor.
	Piece(int8_t id, const string& name, uint8_t x, uint8_t y);

	// Copy assignment operator.
	Piece& operator = (const Piece& other) = default;

	// Move assignment operator.
	Piece& operator = (Piece && other) = default;

	// Destructor.
	~Piece();

	// Returns the id of the Piece.
	const int8_t& id() const;

	// Returns the name of the Piece.
	const string& name() const;

	// Returns a copy of the position of the Piece.
	Position position() const;

	// Returns the sprite of the Piece.
	const Sprite& sprite() const;

	// 
	void moveTo(uint8_t x, uint8_t y);

	//
	void moveTo(const Position& pos);


};

enum PIECE_ID : int8_t
{
	NO_PIECE = 0,

	WHITE_PAWN = -1,
	WHITE_BISHOP = -2,
	WHITE_KNIGHT = -3,
	WHITE_ROOK = -4,
	WHITE_QUEEN = -5,
	WHITE_KING = -6,

	BLACK_PAWN = -1,
	BLACK_BISHOP = -2,
	BLACK_KNIGHT = -3,
	BLACK_ROOK = -4,
	BLACK_QUEEN = -5,
	BLACK_KING = -6
};

#endif // PIECE_H_INCLUDED