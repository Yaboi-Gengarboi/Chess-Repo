// Standard Chess
// main.cpp
// Created on 2021-08-18 by Justyn Durnford
// Last modified on 2021-09-04 by Justyn Durnford
// Main source file for the Standard Chess project.

#include <bitset>
using std::bitset;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;

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
using jlib::FixedMatrix;
using jlib::u8;
using jlib::Vector2i;
using jlib::Vector2uc;
using namespace jlib;

#include "Piece.hpp"

bool loadTextures()
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

// Flags:
// - flags[0]: Is it Whites's turn?
// - flags[1]: Is White in check?
// - flags[2]: Is Black in check?
// - flags[3]: Is player moving a piece?
bitset<4> flags;

FixedArray<string, 8> to_string(const FixedMatrix<Piece*, 8, 8>& board)
{
	FixedArray<string, 8> arr;

	for (size_t row_i = 0; row_i < 8; ++row_i)
	{
		arr[row_i].reserve(27);
		arr[row_i] += "{ ";

		for (size_t col_i = 0; col_i < 7; ++col_i)
		{
			if (board(row_i, col_i) == nullptr)
				arr[row_i] += "00";
			else
			{
				if (board(row_i, col_i)->getID() < 10)
					arr[row_i] += "0" + to_string(board(row_i, col_i)->getID());
				else
					arr[row_i] += to_string(board(row_i, col_i)->getID());
			}

			arr[row_i] += " ";
		}

		if (board(row_i, 7) == nullptr)
			arr[row_i] += "00";
		else
		{
			if (board(row_i, 7)->getID() < 10)
				arr[row_i] += "0" + to_string(board(row_i, 7)->getID());
			else
				arr[row_i] += to_string(board(row_i, 7)->getID());
		}
		arr[row_i] += " }";
	}

	return arr;
}

int main()
{
	RenderWindow window(VideoMode(800, 800), "Standard Chess", sf::Style::Titlebar | sf::Style::Close);

	Font font;
	if (!font.loadFromFile("textures/arial.ttf"))
		return -1;

	#ifdef _DEBUG

		string mouse_pos_str;
		Text mouse_pos_text;
		mouse_pos_text.setFont(font);
		mouse_pos_text.setCharacterSize(36);
		mouse_pos_text.setFillColor(sf::Color(jlib::Color::Yellow));
		mouse_pos_text.setOutlineColor(sf::Color(jlib::Color::Black));
		mouse_pos_text.setOutlineThickness(3.0f);

		string board_pos_str;
		Text board_pos_text;
		board_pos_text.setPosition(0.0f, 36.0f);
		board_pos_text.setFont(font);
		board_pos_text.setCharacterSize(36);
		board_pos_text.setFillColor(sf::Color(jlib::Color::Yellow));
		board_pos_text.setOutlineColor(sf::Color(jlib::Color::Black));
		board_pos_text.setOutlineThickness(3.0f);

		string flags_str;
		Text flags_text;
		flags_text.setPosition(0.0f, 72.0f);
		flags_text.setFont(font);
		flags_text.setCharacterSize(36);
		flags_text.setFillColor(sf::Color(jlib::Color::Yellow));
		flags_text.setOutlineColor(sf::Color(jlib::Color::Black));
		flags_text.setOutlineThickness(3.0f);

		string piece_str;
		Text piece_text;
		piece_text.setPosition(0.0f, 108.0f);
		piece_text.setFont(font);
		piece_text.setCharacterSize(36);
		piece_text.setFillColor(sf::Color(jlib::Color::Yellow));
		piece_text.setOutlineColor(sf::Color(jlib::Color::Black));
		piece_text.setOutlineThickness(3.0f);

		FixedArray<string, 8> board_strs;

		Texture red_square_texture;
		if (!red_square_texture.loadFromFile("textures/red_square.png"))
			return -1;

		FixedMatrix<Sprite, 8, 8> red_square_sprites;

		for (size_t row_i = 0; row_i < 8; ++row_i)
		{
			for (size_t col_i = 0; col_i < 8; ++col_i)
			{
				red_square_sprites(row_i, col_i).setTexture(red_square_texture);
				red_square_sprites(row_i, col_i).setPosition(row_i * 100.0f, col_i * 100.0f);
			}
		}

		bool has_board_changed = false;

	#endif // #ifdef _DEBUG

	if (!loadTextures())
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

	for (size_t row_i = 2; row_i < 6; ++row_i)
	{
		for (size_t col_i = 0; col_i < 8; ++col_i)
			board(row_i, col_i) = nullptr;
	}

	// Set Piece board positions.
	board(0, 0)->setBoardPosition(Vector2i(0, 0));
	board(0, 1)->setBoardPosition(Vector2i(1, 0));
	board(0, 2)->setBoardPosition(Vector2i(2, 0));
	board(0, 3)->setBoardPosition(Vector2i(3, 0));
	board(0, 4)->setBoardPosition(Vector2i(4, 0));
	board(0, 5)->setBoardPosition(Vector2i(5, 0));
	board(0, 6)->setBoardPosition(Vector2i(6, 0));
	board(0, 7)->setBoardPosition(Vector2i(7, 0));
	board(1, 0)->setBoardPosition(Vector2i(0, 1));
	board(1, 1)->setBoardPosition(Vector2i(1, 1));
	board(1, 2)->setBoardPosition(Vector2i(2, 1));
	board(1, 3)->setBoardPosition(Vector2i(3, 1));
	board(1, 4)->setBoardPosition(Vector2i(4, 1));
	board(1, 5)->setBoardPosition(Vector2i(5, 1));
	board(1, 6)->setBoardPosition(Vector2i(6, 1));
	board(1, 7)->setBoardPosition(Vector2i(7, 1));
	board(6, 0)->setBoardPosition(Vector2i(0, 6));
	board(6, 1)->setBoardPosition(Vector2i(1, 6));
	board(6, 2)->setBoardPosition(Vector2i(2, 6));
	board(6, 3)->setBoardPosition(Vector2i(3, 6));
	board(6, 4)->setBoardPosition(Vector2i(4, 6));
	board(6, 5)->setBoardPosition(Vector2i(5, 6));
	board(6, 6)->setBoardPosition(Vector2i(6, 6));
	board(6, 7)->setBoardPosition(Vector2i(7, 6));
	board(7, 0)->setBoardPosition(Vector2i(0, 7));
	board(7, 1)->setBoardPosition(Vector2i(1, 7));
	board(7, 2)->setBoardPosition(Vector2i(2, 7));
	board(7, 3)->setBoardPosition(Vector2i(3, 7));
	board(7, 4)->setBoardPosition(Vector2i(4, 7));
	board(7, 5)->setBoardPosition(Vector2i(5, 7));
	board(7, 6)->setBoardPosition(Vector2i(6, 7));
	board(7, 7)->setBoardPosition(Vector2i(7, 7));

	// Setup valid moves.
	board(0, 0)->updateValidMoves();
	board(0, 1)->updateValidMoves();
	board(0, 2)->updateValidMoves();
	board(0, 3)->updateValidMoves();
	board(0, 4)->updateValidMoves();
	board(0, 5)->updateValidMoves();
	board(0, 6)->updateValidMoves();
	board(0, 7)->updateValidMoves();
	board(1, 0)->updateValidMoves();
	board(1, 1)->updateValidMoves();
	board(1, 2)->updateValidMoves();
	board(1, 3)->updateValidMoves();
	board(1, 4)->updateValidMoves();
	board(1, 5)->updateValidMoves();
	board(1, 6)->updateValidMoves();
	board(1, 7)->updateValidMoves();
	board(6, 0)->updateValidMoves();
	board(6, 1)->updateValidMoves();
	board(6, 2)->updateValidMoves();
	board(6, 3)->updateValidMoves();
	board(6, 4)->updateValidMoves();
	board(6, 5)->updateValidMoves();
	board(6, 6)->updateValidMoves();
	board(6, 7)->updateValidMoves();
	board(7, 0)->updateValidMoves();
	board(7, 1)->updateValidMoves();
	board(7, 2)->updateValidMoves();
	board(7, 3)->updateValidMoves();
	board(7, 4)->updateValidMoves();
	board(7, 5)->updateValidMoves();
	board(7, 6)->updateValidMoves();
	board(7, 7)->updateValidMoves();

	flags[0] = true;

	Piece* piece = nullptr;
	Piece* moving_piece = nullptr;
	Vector2i mouse_pos;
	Vector2i board_pos;
	Event event;

	// Main window loop.
	while (window.isOpen())
	{
		mouse_pos = sf::Mouse::getPosition(window);
		board_pos = (mouse_pos / 100);

		if (moving_piece != nullptr)
			moving_piece->getSprite().setPosition(mouse_pos.x - 50, mouse_pos.y - 50);

		#ifdef _DEBUG

			mouse_pos_str = mouse_pos.toString();
			board_pos_str = board_pos.toString();
			flags_str = reverse_str(flags.to_string());
			
			if (is_within_inclusive(board_pos.x, 0, 7) && is_within_inclusive(board_pos.y, 0, 7))
				piece = board(board_pos.y, board_pos.x);
			else
				piece = nullptr;

			if (piece != nullptr)
				piece_str = piece->getName() + ": " + piece->getBoardPosition().toString();
			else
				piece_str = "";

			piece_text.setString(piece_str);

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
					
					if (event.key.code == sf::Mouse::Button::Left)
					{
						if (!flags[3])
						{
							if (flags[0])
							{
								if (isPieceWhite(board_pos.x, board_pos.y))
								{
									moving_piece = board(board_pos.y, board_pos.x);
									moving_piece->updateValidMoves();
									flags[3] = true;
								}
							}
							else
							{
								if (isPieceBlack(board_pos.x, board_pos.y))
								{
									moving_piece = board(board_pos.y, board_pos.x);
									moving_piece->updateValidMoves();
									flags[3] = true;
								}
							}
						}
						else if (flags[3])
						{
							if (moving_piece->canMoveTo(board_pos))
							{
								board(moving_piece->getBoardPosition().y, moving_piece->getBoardPosition().x) = nullptr;
								board(board_pos.y, board_pos.x) = moving_piece;
								moving_piece->setBoardPosition(board_pos);
								moving_piece = nullptr;
								flags.flip(0);
								flags[3] = false;
								has_board_changed = true;
							}
						}
					}
					else if (event.key.code == sf::Mouse::Button::Right)
					{
						if (flags[3])
						{
							moving_piece->getSprite().setPosition(moving_piece->getBoardPosition().x * 100, moving_piece->getBoardPosition().y * 100);
							moving_piece = nullptr;
							flags[3] = false;
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

		// Print current board layout.
		#ifdef _DEBUG

			if (has_board_changed)
			{
				board_strs = to_string(board);

				for (size_t i = 0; i < 8; ++i)
					cout << board_strs[i] << endl;
				cout << endl;
			}

			has_board_changed = false;

		#endif // #ifdef _DEBUG

		// Draw possible moves.
		#ifdef _DEBUG

			if (moving_piece != nullptr)
			{
				const vector<Vector2i>& validMoves = moving_piece->getValidMoves();
				for (const Vector2i& elem : validMoves)
					window.draw(red_square_sprites(elem.x, elem.y));
			}

		#endif // #ifdef _DEBUG

		// Draw text.
		#ifdef _DEBUG

			window.draw(mouse_pos_text);
			window.draw(board_pos_text);
			window.draw(flags_text);
			window.draw(piece_text);

		#endif // #ifdef _DEBUG

		window.display();
	}

	return 0;  
}