// Chess
// JMatrix.h
// Justyn Durnford
// Created on 2020-10-12
// Last updated on 2020-12-23
// Header file for the JMatrix template class.

#ifndef JMATRIX_H_INCLUDED
#define JMATRIX_H_INCLUDED

#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <utility>

// This class is able to function as a 
//
//
template <std::semiregular T>
class JMatrix
{
	public:

	using value_type = T;
	using size_type = std::size_t;

	private:

	std::vector<std::vector<value_type>> matrix_;
	size_type row_ = 0;
	size_type col_ = 0;

	void checkBounds(const size_type& row, const size_type& col)
	{
		if (row >= row_)
			throw std::out_of_range("Invalid row index");

		if (col >= col_)
			throw std::out_of_range("Invalid column index");
	}

	public:

	JMatrix() = default;

	JMatrix(const size_type& row, const size_type& col)
	{
		try
		{
			row_ = row;
			col_ = col;
			matrix_.resize(row_);
			matrix_.shrink_to_fit();

			for (size_type r = 0; r < row_; ++r)
			{
				matrix_[r].resize(col_);
				matrix_[r].shrink_to_fit();
			}
		}
		catch (...)
		{
			throw;
		}
	}

	JMatrix(const size_type& row, const size_type& col, const value_type& val)
	{
		try
		{
			row_ = row;
			col_ = col;
			matrix_.resize(row_);
			matrix_.shrink_to_fit();

			for (size_type r = 0; r < row_; ++r)
			{
				matrix_[r].resize(col_, val);
				matrix_[r].shrink_to_fit();
			}
		}
		catch (...)
		{
			throw;
		}
	}

	JMatrix(const JMatrix& other)
	{
		try
		{
			matrix_ = other.matrix_;
			matrix_.shrink_to_fit();
			row_ = other.row_;
			col_ = other.col_;
		}
		catch (...)
		{
			throw;
		}
	}

	JMatrix(JMatrix&& other)
	{
		try
		{
			matrix_ = std::move(other.matrix_);
			row_ = other.row_;
			col_ = other.col_;
		}
		catch (...)
		{
			throw;
		}
	}

	JMatrix& operator = (const JMatrix& other)
	{
		try
		{
			matrix_ = other.matrix_;
			matrix_.shrink_to_fit();
			row_ = other.row_;
			col_ = other.col_;
		}
		catch (...)
		{
			throw;
		}

		return *this;
	}

	JMatrix& operator = (JMatrix&& other)
	{
		try
		{
			matrix_ = std::move(other.matrix_);
			row_ = other.row_;
			col_ = other.col_;
		}
		catch (...)
		{
			throw;
		}

		return *this;
	}

	JMatrix& operator = (const std::vector<std::vector<T>>& matrix)
	{
		row_ = matrix.size();
		size_type col = 0;

		for (size_type r = 0; r < row_; ++r)
		{
			if (matrix[r].size() > col)
				col = matrix[r].size();
		}

		col_ = col;

		matrix_.resize(row_);
		matrix_.shrink_to_fit();

		for (size_type r = 0; r < row_; ++r)
		{
			matrix_[r].resize(col_);
			matrix_[r].shrink_to_fit();
		}

		for (size_type r = 0; r < row_; ++r)
		{
			for (size_type c = 0; c < col_; ++c)
				matrix_[r][c] = matrix[r][c];
		}

		return *this;
	}

	~JMatrix() = default;

	size_type rowSize() const
	{
		return row_;
	}

	size_type colSize() const
	{
		return col_;
	}

	bool empty() const
	{
		return row_ == 0;
	}

	value_type& at(const size_type& row, const size_type& col)
	{
		checkBounds(row, col);
		return matrix_[row][col];
	}

	const value_type& at(const size_type& row, const size_type& col) const
	{
		checkBounds(row, col);
		return matrix_[row][col];
	}

	value_type& operator () (const size_type& row, const size_type& col)
	{
		return matrix_[row][col];
	}

	const value_type& operator () (const size_type& row, const size_type& col) const
	{
		return matrix_[row][col];
	}

	void set(const size_type& row, const size_type& col, const value_type& val)
	{
		checkBounds(row, col);
		matrix_[row][col] = val;
	}

	void resize(const size_type& row, const size_type& col)
	{
		try
		{
			matrix_.resize(row);
			matrix_.shrink_to_fit();
			row_ = row;
			col_ = col;

			for (size_type r = 0; r < row_; ++r)
			{
				matrix_[r].resize(col);
				matrix_[r].shrink_to_fit();
			}
		}
		catch (...)
		{
			throw;
		}
	}
};

#endif // JMATRIX_H_INCLUDED