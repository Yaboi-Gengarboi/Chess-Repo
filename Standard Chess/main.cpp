// Standard Chess
// main.cpp
// Created on 2021-08-18 by Justyn Durnford
// Last modified on 2021-08-21 by Justyn Durnford
// Main source file for the Standard Chess project.

#include <array>
using std::array;

#include <bitset>
using std::bitset;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <utility>
using std::move;
using std::swap;

#include <vector>
using std::vector;

#include <SFML/Graphics.hpp>
using sf::Event;
using sf::Font;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Texture;
using sf::VideoMode;

#include "JLIB.hpp"
using jlib::CMatrix;
using jlib::u8;
using jlib::Vector2i;
using jlib::Vector2uc;
using namespace jlib;

#include "Convert.hpp"

class Piece;

CMatrix<Piece*, 8, 8> board;

bool loadTextures(array<Texture, 15>& textures)
{
	if (!textures[0].loadFromFile("textures/board.png"))
		return false;
	if (!textures[1].loadFromFile("textures/w_pawn.png"))
		return false;
	if (!textures[2].loadFromFile("textures/w_bishop.png"))
		return false;
	if (!textures[3].loadFromFile("textures/w_knight.png"))
		return false;
	if (!textures[4].loadFromFile("textures/w_rook.png"))
		return false;
	if (!textures[5].loadFromFile("textures/w_queen.png"))
		return false;
	if (!textures[6].loadFromFile("textures/w_king.png"))
		return false;
	if (!textures[7].loadFromFile("textures/b_pawn.png"))
		return false;
	if (!textures[8].loadFromFile("textures/b_bishop.png"))
		return false;
	if (!textures[9].loadFromFile("textures/b_knight.png"))
		return false;
	if (!textures[10].loadFromFile("textures/b_rook.png"))
		return false;
	if (!textures[11].loadFromFile("textures/b_queen.png"))
		return false;
	if (!textures[12].loadFromFile("textures/b_king.png"))
		return false;
	if (!textures[13].loadFromFile("textures/w_transform.png"))
		return false;
	if (!textures[14].loadFromFile("textures/b_transform.png"))
		return false;

	return true;
}

class Piece
{
	public:

	enum : u8
	{
		NoPiece     =  0,
		WhitePawn   =  1,
		WhiteBishop =  2,
		WhiteKnight =  3,
		WhiteRook   =  4,
		WhiteQueen  =  5,
		WhiteKing   =  6,
		BlackPawn   =  7,
		BlackBishop =  8,
		BlackKnight =  9,
		BlackRook   = 10,
		BlackQueen  = 11,
		BlackKing   = 12
	};

	private:

	u8 _id;
	string _name;
	Vector2i _boardPos;
	Sprite _spr;
	vector<u8> _validMoves;

	public:

	Piece()
	{
		_id = 0;
	}

	Piece(u8 id, const string& name, const Vector2i& boardPos, Texture& texture)
	{
		_id = id;
		_name = name;
		_boardPos = boardPos;
		_spr.setTexture(texture);
	}

	u8 getID() const
	{
		return _id;
	}

	void setID(u8 id)
	{
		_id = id;
	}

	const string& getName() const
	{
		return _name;
	}

	void setName(const string& name)
	{
		_name = name;
	}

	const Vector2i& getBoardPosition() const
	{
		return _boardPos;
	}

	void setBoardPosition(const Vector2i& boardPos)
	{
		_boardPos = boardPos;
		_validMoves.clear();

		// Update valid moves.
		switch (_id)
		{
			case WhitePawn:

				if (_boardPos.y == 6) // Can move 2 spaces forwards.
				{

				}

				break;

			default: break;
		}
	}

	Sprite& getSprite()
	{
		return _spr;
	}

	void setSprite(Sprite& spr)
	{
		_spr = spr;
	}

	const vector<u8>& getValidMoves() const
	{
		return _validMoves;
	}

	bool canMoveTo(const Vector2i& boardPos) const
	{
		return true;
	}
};

// Flags:
// - flags[0]: Is it Whites's turn?
// - flags[1]: Is White in check?
// - flags[2]: Is Black in check?
// - flags[3]: Is player moving a piece?
bitset<4> flags;

int main()
{
	RenderWindow window(VideoMode(800, 800), "Standard Chess", sf::Style::Titlebar | sf::Style::Close);

	Font font;
	if (!font.loadFromFile("textures/arial.ttf"))
		return -1;

	string mouse_pos_str;
	Text mouse_pos_text;
	mouse_pos_text.setFont(font);
	mouse_pos_text.setCharacterSize(36);
	mouse_pos_text.setFillColor(create_from(jlib::Color::Yellow));
	mouse_pos_text.setOutlineColor(create_from(jlib::Color::Black));
	mouse_pos_text.setOutlineThickness(3.0f);

	string board_pos_str;
	Text board_pos_text;
	board_pos_text.setPosition(0.0f, 36.0f);
	board_pos_text.setFont(font);
	board_pos_text.setCharacterSize(36);
	board_pos_text.setFillColor(create_from(jlib::Color::Yellow));
	board_pos_text.setOutlineColor(create_from(jlib::Color::Black));
	board_pos_text.setOutlineThickness(3.0f);

	string flags_str;
	Text flags_text;
	flags_text.setPosition(0.0f, 72.0f);
	flags_text.setFont(font);
	flags_text.setCharacterSize(36);
	flags_text.setFillColor(create_from(jlib::Color::Yellow));
	flags_text.setOutlineColor(create_from(jlib::Color::Black));
	flags_text.setOutlineThickness(3.0f);

	string moving_piece_str;
	Text moving_piece_text;
	moving_piece_text.setPosition(0.0f, 108.0f);
	moving_piece_text.setFont(font);
	moving_piece_text.setCharacterSize(36);
	moving_piece_text.setFillColor(create_from(jlib::Color::Yellow));
	moving_piece_text.setOutlineColor(create_from(jlib::Color::Black));
	moving_piece_text.setOutlineThickness(3.0f);

	// Load textures.
	array<Texture, 15> textures;
	if (!loadTextures(textures))
		return -1;

	// Set board sprite.
	Sprite boardSprite;
	boardSprite.setTexture(textures[0]);

	// Create pieces.
	Piece whitePawnA(Piece::WhitePawn, "White Pawn", Vector2i(0, 6), textures[1]);
	Piece whitePawnB(Piece::WhitePawn, "White Pawn", Vector2i(1, 6), textures[1]);
	Piece whitePawnC(Piece::WhitePawn, "White Pawn", Vector2i(2, 6), textures[1]);
	Piece whitePawnD(Piece::WhitePawn, "White Pawn", Vector2i(3, 6), textures[1]);
	Piece whitePawnE(Piece::WhitePawn, "White Pawn", Vector2i(4, 6), textures[1]);
	Piece whitePawnF(Piece::WhitePawn, "White Pawn", Vector2i(5, 6), textures[1]);
	Piece whitePawnG(Piece::WhitePawn, "White Pawn", Vector2i(6, 6), textures[1]);
	Piece whitePawnH(Piece::WhitePawn, "White Pawn", Vector2i(7, 6), textures[1]);
	Piece whiteBishopC(Piece::WhiteBishop, "White Bishop", Vector2i(2, 7), textures[2]);
	Piece whiteBishopF(Piece::WhiteBishop, "White Bishop", Vector2i(5, 7), textures[2]);
	Piece whiteKnightB(Piece::WhiteKnight, "White Knight", Vector2i(1, 7), textures[3]);
	Piece whiteKnightG(Piece::WhiteKnight, "White Knight", Vector2i(6, 7), textures[3]);
	Piece whiteRookA(Piece::WhiteRook, "White Rook", Vector2i(0, 7), textures[4]);
	Piece whiteRookH(Piece::WhiteRook, "White Rook", Vector2i(7, 7), textures[4]);
	Piece whiteQueen(Piece::WhiteQueen, "White Queen", Vector2i(3, 7), textures[5]);
	Piece whiteKing(Piece::WhiteKing, "White King", Vector2i(4, 7), textures[6]);

	Piece blackPawnA(Piece::BlackPawn, "Black Pawn", Vector2i(0, 1), textures[7]);
	Piece blackPawnB(Piece::BlackPawn, "Black Pawn", Vector2i(1, 1), textures[7]);
	Piece blackPawnC(Piece::BlackPawn, "Black Pawn", Vector2i(2, 1), textures[7]);
	Piece blackPawnD(Piece::BlackPawn, "Black Pawn", Vector2i(3, 1), textures[7]);
	Piece blackPawnE(Piece::BlackPawn, "Black Pawn", Vector2i(4, 1), textures[7]);
	Piece blackPawnF(Piece::BlackPawn, "Black Pawn", Vector2i(5, 1), textures[7]);
	Piece blackPawnG(Piece::BlackPawn, "Black Pawn", Vector2i(6, 1), textures[7]);
	Piece blackPawnH(Piece::BlackPawn, "Black Pawn", Vector2i(7, 1), textures[7]);
	Piece blackBishopC(Piece::BlackBishop, "Black Bishop", Vector2i(2, 1), textures[8]);
	Piece blackBishopF(Piece::BlackBishop, "Black Bishop", Vector2i(5, 1), textures[8]);
	Piece blackKnightB(Piece::BlackKnight, "Black Knight", Vector2i(1, 1), textures[9]);
	Piece blackKnightG(Piece::BlackKnight, "Black Knight", Vector2i(6, 1), textures[9]);
	Piece blackRookA(Piece::BlackRook, "Black Rook", Vector2i(0, 1), textures[10]);
	Piece blackRookH(Piece::BlackRook, "Black Rook", Vector2i(7, 1), textures[10]);
	Piece blackQueen(Piece::BlackQueen, "Black Queen", Vector2i(3, 1), textures[11]);
	Piece blackKing(Piece::BlackKing, "Black King", Vector2i(4, 1), textures[12]);

	// Scale Piece sprites.
	whitePawnA.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnB.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnC.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnD.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnE.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnF.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnG.getSprite().setScale(0.78125f, 0.78125f);
	whitePawnH.getSprite().setScale(0.78125f, 0.78125f);
	whiteBishopC.getSprite().setScale(0.78125f, 0.78125f);
	whiteBishopF.getSprite().setScale(0.78125f, 0.78125f);
	whiteKnightB.getSprite().setScale(0.78125f, 0.78125f);
	whiteKnightG.getSprite().setScale(0.78125f, 0.78125f);
	whiteRookA.getSprite().setScale(0.78125f, 0.78125f);
	whiteRookH.getSprite().setScale(0.78125f, 0.78125f);
	whiteQueen.getSprite().setScale(0.78125f, 0.78125f);
	whiteKing.getSprite().setScale(0.78125f, 0.78125f);

	blackPawnA.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnB.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnC.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnD.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnE.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnF.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnG.getSprite().setScale(0.78125f, 0.78125f);
	blackPawnH.getSprite().setScale(0.78125f, 0.78125f);
	blackBishopC.getSprite().setScale(0.78125f, 0.78125f);
	blackBishopF.getSprite().setScale(0.78125f, 0.78125f);
	blackKnightB.getSprite().setScale(0.78125f, 0.78125f);
	blackKnightG.getSprite().setScale(0.78125f, 0.78125f);
	blackRookA.getSprite().setScale(0.78125f, 0.78125f);
	blackRookH.getSprite().setScale(0.78125f, 0.78125f);
	blackQueen.getSprite().setScale(0.78125f, 0.78125f);
	blackKing.getSprite().setScale(0.78125f, 0.78125f);

	// Set Piece positions.
	whitePawnA.getSprite().setPosition(0.0f, 600.0f);
	whitePawnB.getSprite().setPosition(100.0f, 600.0f);
	whitePawnC.getSprite().setPosition(200.0f, 600.0f);
	whitePawnD.getSprite().setPosition(300.0f, 600.0f);
	whitePawnE.getSprite().setPosition(400.0f, 600.0f);
	whitePawnF.getSprite().setPosition(500.0f, 600.0f);
	whitePawnG.getSprite().setPosition(600.0f, 600.0f);
	whitePawnH.getSprite().setPosition(700.0f, 600.0f);
	whiteBishopC.getSprite().setPosition(200.0f, 700.0f);
	whiteBishopF.getSprite().setPosition(500.0f, 700.0f);
	whiteKnightB.getSprite().setPosition(100.0f, 700.0f);
	whiteKnightG.getSprite().setPosition(600.0f, 700.0f);
	whiteRookA.getSprite().setPosition(0.0f, 700.0f);
	whiteRookH.getSprite().setPosition(700.0f, 700.0f);
	whiteQueen.getSprite().setPosition(300.0f, 700.0f);
	whiteKing.getSprite().setPosition(400.0f, 700.0f);

	blackPawnA.getSprite().setPosition(0.0f, 100.0f);
	blackPawnB.getSprite().setPosition(100.0f, 100.0f);
	blackPawnC.getSprite().setPosition(200.0f, 100.0f);
	blackPawnD.getSprite().setPosition(300.0f, 100.0f);
	blackPawnE.getSprite().setPosition(400.0f, 100.0f);
	blackPawnF.getSprite().setPosition(500.0f, 100.0f);
	blackPawnG.getSprite().setPosition(600.0f, 100.0f);
	blackPawnH.getSprite().setPosition(700.0f, 100.0f);
	blackBishopC.getSprite().setPosition(200.0f, 0.0f);
	blackBishopF.getSprite().setPosition(500.0f, 0.0f);
	blackKnightB.getSprite().setPosition(100.0f, 0.0f);
	blackKnightG.getSprite().setPosition(600.0f, 0.0f);
	blackRookA.getSprite().setPosition(0.0f, 0.0f);
	blackRookH.getSprite().setPosition(700.0f, 0.0f);
	blackQueen.getSprite().setPosition(300.0f, 0.0f);
	blackKing.getSprite().setPosition(400.0f, 0.0f);

	// Setup board.
	board(0, 0) = &blackRookA;
	board(0, 1) = &blackKnightB;
	board(0, 2) = &blackBishopC;
	board(0, 3) = &blackQueen;
	board(0, 4) = &blackKing;
	board(0, 5) = &blackBishopF;
	board(0, 6) = &blackKnightG;
	board(0, 7) = &blackRookH;
	board(1, 0) = &blackPawnA;
	board(1, 1) = &blackPawnB;
	board(1, 2) = &blackPawnC;
	board(1, 3) = &blackPawnD;
	board(1, 4) = &blackPawnE;
	board(1, 5) = &blackPawnF;
	board(1, 6) = &blackPawnG;
	board(1, 7) = &blackPawnH;
	board(6, 0) = &whitePawnA;
	board(6, 1) = &whitePawnB;
	board(6, 2) = &whitePawnC;
	board(6, 3) = &whitePawnD;
	board(6, 4) = &whitePawnE;
	board(6, 5) = &whitePawnF;
	board(6, 6) = &whitePawnG;
	board(6, 7) = &whitePawnH;
	board(7, 0) = &whiteRookA;
	board(7, 1) = &whiteKnightB;
	board(7, 2) = &whiteBishopC;
	board(7, 3) = &whiteQueen;
	board(7, 4) = &whiteKing;
	board(7, 5) = &whiteBishopF;
	board(7, 6) = &whiteKnightG;
	board(7, 7) = &whiteRookH;

	for (size_t i = 16; i < 48; ++i)
		board[i] = nullptr;

	flags[0] = true;

	Piece* moving_piece = nullptr;
	Vector2i mouse_pos;
	Vector2i board_pos;
	Event event;

	// Main window loop.
	while (window.isOpen())
	{
		copy(sf::Mouse::getPosition(window), mouse_pos);
		board_pos = (mouse_pos / 100);

		if (moving_piece != nullptr)
			moving_piece->getSprite().setPosition(mouse_pos.x - 50, mouse_pos.y - 50);

		#ifdef _DEBUG

			mouse_pos_str = mouse_pos.toString();
			board_pos_str = board_pos.toString();
			flags_str = reverse_str(flags.to_string());
			
			if (moving_piece != nullptr)
				moving_piece_str = moving_piece->getName() + ": " + moving_piece->getBoardPosition().toString();
			else
				moving_piece_str = "";

			moving_piece_text.setString(moving_piece_str);

			mouse_pos_text.setString(mouse_pos_str);
			board_pos_text.setString(board_pos_str);
			flags_text.setString(flags_str);

		#endif // #ifdef _DEBUG

		// Handle events.
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					window.close();
				break;

				case Event::MouseButtonPressed:
					
					if (event.key.code == Mouse::Button::Left)
					{
						if (!flags[3])
						{
							if (flags[0])
							{
								if (board(board_pos.y, board_pos.x) != nullptr && board(board_pos.y, board_pos.x)->getID() < 7)
								{
									swap(moving_piece, board(board_pos.y, board_pos.x));
									flags[3] = true;
								}
							}
							else
							{
								if (board(board_pos.y, board_pos.x) != nullptr && board(board_pos.y, board_pos.x)->getID() > 6)
								{
									swap(moving_piece, board(board_pos.y, board_pos.x));
									flags[3] = true;
								}
							}
						}
						else if (flags[3])
						{
							if (board(static_cast<Vector2<size_t>>(board_pos)) == nullptr)
							{
								if (moving_piece->canMoveTo(board_pos))
								{
									moving_piece->setBoardPosition(board_pos);
									moving_piece->getSprite().setPosition(board_pos.x * 100, board_pos.y * 100);
									swap(moving_piece, board(static_cast<Vector2<size_t>>(board_pos)));
									flags.flip(0);
									flags[3] = false;
								}
							}
						}
					}

				break;

				default: break;
			}
		}

		window.clear();

		// Draw sprites.
		window.draw(boardSprite);
		for (size_t i = 0; i < board.size(); ++i)
		{
			if (board[i] != nullptr)
				window.draw(board[i]->getSprite());
		}

		if (flags[3])
			window.draw(moving_piece->getSprite());

		// Draw text.
		#ifdef _DEBUG

			window.draw(mouse_pos_text);
			window.draw(board_pos_text);
			window.draw(flags_text);
			window.draw(moving_piece_text);

		#endif

		window.display();
	}

	return 0;  
}