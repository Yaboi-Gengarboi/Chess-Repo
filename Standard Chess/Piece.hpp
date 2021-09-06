// Standard Chess
// Piece.hpp
// Created on 2021-08-28 by Justyn Durnford
// Last modified on 2021-09-06 by Justyn Durnford
// Header file for the Piece class.

#pragma once

#include "JLIB.hpp"
using namespace jlib;

#include "SFML/Graphics.hpp"
using sf::Sprite;
using sf::Texture;

#include <string>
using std::string;

#include <vector>
using std::vector;

class Piece
{
	public:

	enum : u8
	{
		NoPiece     = 0,
		WhitePawn   = 1,
		WhiteBishop = 2,
		WhiteKnight = 3,
		WhiteRook   = 4,
		WhiteQueen  = 5,
		WhiteKing   = 6,
		BlackPawn   = 7,
		BlackBishop = 8,
		BlackKnight = 9,
		BlackRook   = 10,
		BlackQueen  = 11,
		BlackKing   = 12
	};

	private:

	u8 _id;
	string _name;
	Vector2i _pos;
	Sprite _spr;
	vector<Vector2i> _validMoves;

	public:

	// Default constructor.
	Piece();

	// Primary constructor.
	Piece(u8 id, const string& name, const Vector2i& pos, Texture& texture);

	// Returns the id of the Piece.
	u8 getID() const;

	// Sets the id of the Piece.
	void setID(u8 id);

	// Returns the name of the Piece.
	const string& getName() const;

	// Sets the name of the Piece.
	void setName(const string& name);

	// Returns the position of the Piece.
	const Vector2i& getBoardPosition() const;

	// Sets the position of the Piece.
	void setBoardPosition(const Vector2i& pos);

	// Returns the sprite of the Piece.
	Sprite& getSprite();

	// Sets the sprite of the Piece.
	void setSprite(Sprite& spr);

	// Returns the vector of valid moves of the Piece.
	const vector<Vector2i>& getValidMoves() const;

	// Updates the Piece's valid moves.
	void updateValidMoves();

	// Returns true if the Piece can move to the given position.
	bool canMoveTo(const Vector2i& pos) const;
};

extern FixedMatrix<Piece*, 8, 8> board;
extern FixedArray<Texture, 15> textures;

bool isPieceWhite(size_t x, size_t y);

bool isPieceBlack(size_t x, size_t y);

bool isSpaceEmpty(size_t x, size_t y);

bool isSpaceUpEmpty(size_t x, size_t y);

bool isSpaceUpLeftEmpty(size_t x, size_t y);

bool isSpaceUpRightEmpty(size_t x, size_t y);

bool isSpaceLeftEmpty(size_t x, size_t y);

bool isSpaceRightEmpty(size_t x, size_t y);

bool isSpaceDownEmpty(size_t x, size_t y);

bool isSpaceDownLeftEmpty(size_t x, size_t y);

bool isSpaceDownRightEmpty(size_t x, size_t y);