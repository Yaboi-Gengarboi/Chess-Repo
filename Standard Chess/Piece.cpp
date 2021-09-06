// Standard Chess
// Piece.cpp
// Created on 2021-09-04 by Justyn Durnford
// Last modified on 2021-09-06 by Justyn Durnford
// Source file for the Piece class.

#include "Piece.hpp"

FixedMatrix<Piece*, 8, 8> board;
FixedArray<Texture, 15> textures;

Piece::Piece()
{
	_id = 0;
}

Piece::Piece(u8 id, const string& name, const Vector2i& pos, Texture& texture)
{
	_id = id;
	_name = name;
	_pos = pos;
	_spr.setTexture(texture);
}

u8 Piece::getID() const
{
	return _id;
}

void Piece::setID(u8 id)
{
	_id = id;
}

const string& Piece::getName() const
{
	return _name;
}

void Piece::setName(const string& name)
{
	_name = name;
}

const Vector2i& Piece::getBoardPosition() const
{
	return _pos;
}

void Piece::setBoardPosition(const Vector2i& pos)
{
	_pos = pos;
	_spr.setPosition(100.0f * _pos.x, 100.0f * _pos.y);
}

Sprite& Piece::getSprite()
{
	return _spr;
}

void Piece::setSprite(Sprite& spr)
{
	_spr = spr;
}

const vector<Vector2i>& Piece::getValidMoves() const
{
	return _validMoves;
}

void Piece::updateValidMoves()
{
	_validMoves.clear();

	switch (_id)
	{
		case Piece::WhitePawn:

			if (_pos.y == 6 && isSpaceEmpty(_pos.x, 4))
				_validMoves.push_back(Vector2i(_pos.x, 4));
			if (isSpaceUpEmpty(_pos.x, _pos.y))
				_validMoves.push_back(Vector2i(_pos.x, _pos.y - 1));
			if (isPieceBlack(_pos.x - 1, _pos.y - 1))
				_validMoves.push_back(Vector2i(_pos.x - 1, _pos.y - 1));
			if (isPieceBlack(_pos.x + 1, _pos.y - 1))
				_validMoves.push_back(Vector2i(_pos.x + 1, _pos.y - 1));

		break;

		case Piece::BlackPawn:

			if (_pos.y == 1 && isSpaceEmpty(_pos.x, 3))
				_validMoves.push_back(Vector2i(_pos.x, 3));
			if (isSpaceDownEmpty(_pos.x, _pos.y))
				_validMoves.push_back(Vector2i(_pos.x, _pos.y + 1));
			if (isPieceWhite(_pos.x - 1, _pos.y + 1))
				_validMoves.push_back(Vector2i(_pos.x - 1, _pos.y + 1));
			if (isPieceWhite(_pos.x + 1, _pos.y + 1))
				_validMoves.push_back(Vector2i(_pos.x + 1, _pos.y + 1));

		break;

		default: break;
	}
}

bool Piece::canMoveTo(const Vector2i& pos) const
{
	for (const Vector2i& elem : _validMoves)
	{
		if (elem == pos)
			return true;
	}

	return false;
}

bool isPieceWhite(size_t x, size_t y)
{
	if (is_within_inclusive(int(x), 0, 7) && is_within_inclusive(int(y), 0, 7))
	{
		Piece* piece = board(y, x);

		if (piece != nullptr)
			return piece->getID() <= 6;
	}

	return false;
}

bool isPieceBlack(size_t x, size_t y)
{
	if (is_within_inclusive(int(x), 0, 7) && is_within_inclusive(int(y), 0, 7))
	{
		Piece* piece = board(y, x);

		if (piece != nullptr)
			return piece->getID() >= 7;
	}

	return false;
}

bool isSpaceEmpty(size_t x, size_t y)
{
	return board(y, x) == nullptr;
}

bool isSpaceUpEmpty(size_t x, size_t y)
{
	if (y != 0)
		return board(y - 1, x) == nullptr;
	return false;
}

bool isSpaceUpLeftEmpty(size_t x, size_t y)
{
	if (y != 0 && x != 0)
		return board(y - 1, x - 1) == nullptr;
	return false;
}

bool isSpaceUpRightEmpty(size_t x, size_t y)
{
	if (y != 0 && x != 7)
		return board(y - 1, x + 1) == nullptr;
	return false;
}

bool isSpaceLeftEmpty(size_t x, size_t y)
{
	if (x != 0)
		return board(y, x - 1) == nullptr;
	return false;
}

bool isSpaceRightEmpty(size_t x, size_t y)
{
	if (x != 7)
		return board(y, x + 1) == nullptr;
	return false;
}

bool isSpaceDownEmpty(size_t x, size_t y)
{
	if (y != 7)
		return board(y + 1, x) == nullptr;
	return false;
}

bool isSpaceDownLeftEmpty(size_t x, size_t y)
{
	if (y != 7 && x != 0)
		return board(y + 1, x - 1) == nullptr;
	return false;
}

bool isSpaceDownRightEmpty(size_t x, size_t y)
{
	if (y != 7 && x != 7)
		return board(y + 1, x + 1) == nullptr;
	return false;
}