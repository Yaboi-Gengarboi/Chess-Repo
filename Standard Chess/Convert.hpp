// Standard Chess
// Convert.hpp
// Created on 2021-08-21 by Justyn Durnford
// Last modified on 2021-08-21 by Justyn Durnford

#pragma once

#include "JLIB.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

template <jlib::std_arithmetic T>
void copy(const jlib::Vector2<T>& src, sf::Vector2<T>& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

template <jlib::std_arithmetic T>
void copy(const sf::Vector2<T>& src, jlib::Vector2<T>& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

template <jlib::std_arithmetic T>
jlib::Vector2<T> create_from(const sf::Vector2<T>& src)
{
	return Vector2<T>(src.x, src.y);
}

template <jlib::std_arithmetic T>
sf::Vector2<T> create_from(const jlib::Vector2<T>& src)
{
	return sf::Vector2<T>(src.x, src.y);
}

template <jlib::std_arithmetic T>
void copy(const jlib::Vector3<T>& src, sf::Vector3<T>& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

template <jlib::std_arithmetic T>
void copy(const sf::Vector3<T>& src, jlib::Vector3<T>& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

template <jlib::std_arithmetic T>
jlib::Vector3<T> create_from(const sf::Vector3<T>& src)
{
	return Vector3<T>(src.x, src.y, src.z);
}

template <jlib::std_arithmetic T>
sf::Vector3<T> create_from(const jlib::Vector3<T>& src)
{
	return sf::Vector3<T>(src.x, src.y, src.z);
}

void copy(const jlib::Color& src, sf::Color& dst)
{
	dst.r = src.r;
	dst.g = src.g;
	dst.b = src.b;
	dst.a = src.a;
}

void copy(const sf::Color& src, jlib::Color& dst)
{
	dst.r = src.r;
	dst.g = src.g;
	dst.b = src.b;
	dst.a = src.a;
}

jlib::Color create_from(const sf::Color& src)
{
	return jlib::Color(src.r, src.g, src.b, src.a);
}

sf::Color create_from(const jlib::Color& src)
{
	return sf::Color(src.r, src.g, src.b, src.a);
}

template <jlib::std_arithmetic T>
void copy(const jlib::Rect<T>& src, sf::Rect<T>& dst)
{
	dst.left = src.x;
	dst.top = src.y;
	dst.width = src.width;
	dst.height = src.height;
}

template <jlib::std_arithmetic T>
void copy(const sf::Rect<T>& src, jlib::Rect<T>& dst)
{
	dst.x = src.left;
	dst.y = src.top;
	dst.width = src.width;
	dst.height = src.height;
}

template <jlib::std_arithmetic T>
jlib::Rect<T> create_from(const sf::Rect<T>& src)
{
	return jlib::Rect<T>(src.left, src.top, src.width, src.height);
}

template <jlib::std_arithmetic T>
sf::Rect<T> create_from(const jlib::Rect<T>& src)
{
	return sf::Rect<T>(src.x, src.y, src.width, src.height);
}