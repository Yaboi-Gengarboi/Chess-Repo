// JLIB.cpp
// Created on 2021-08-07 by Justyn Durnford
// Last modified on 2021-09-04 by Justyn Durnford

#pragma warning(disable : 4996)
#pragma warning(disable : 4244)

#include "JLIB.hpp"
using namespace jlib;

#include <algorithm>
using std::max;
using std::min;

#include <chrono>
using std::chrono::duration;
using std::chrono::system_clock;
using std::chrono::time_point;

#include <cmath>
using std::acosf;
using std::asinf;
using std::atanf;
using std::cosf;
using std::fabsf;
using std::fmodf;
using std::sinf;
using std::tanf;

#include <codecvt>
using std::codecvt_utf8;

#include <compare>
using std::strong_ordering;

#include <cstddef>
using std::ptrdiff_t;
using std::size_t;

#include <cstring>
using std::memcpy;

#include <initializer_list>
using std::initializer_list;

#include <iostream>
using std::cout;
using std::ostream;
using std::wostream;
using std::endl;

#include <locale>
using std::wstring_convert;

#include <numbers>
using std::numbers::pi_v;

#include <cstddef>
using std::size_t;

#include <stdexcept>
using std::out_of_range;

#include <string>
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Angle::Angle()
	{
		degree = 0.0f;
	}

	Angle::Angle(float Degree)
	{
		degree = Degree;
	}

	Angle& Angle::operator = (float Degree)
	{
		degree = Degree;
		return *this;
	}

	string Angle::toString() const
	{
		return to_string(degree) + '\370';
	}

	constexpr float to_radians(float degree)
	{
		return degree * JLIB_TO_RAD;
	}

	constexpr float to_degrees(float radian)
	{
		return radian * JLIB_TO_DEG;
	}

	float sine(Angle angle)
	{
		if (fmodf(angle.degree, 180.0f) == 0.0f)
			return 0.0f;

		return sinf(to_radians(angle.degree));
	}

	float cosine(Angle angle)
	{
		if ((fmodf(angle.degree, 90.0f) == 0.0f) && ((fmodf(angle.degree, 180.0f) != 0.0f)))
			return 0.0f;

		return cosf(to_radians(angle.degree));
	}

	float tangent(Angle angle)
	{
		return tanf(to_radians(angle.degree));
	}

	Angle arcsine(float value)
	{
		return Angle(to_degrees(asinf(value)));
	}

	Angle arccosine(float value)
	{
		return Angle(to_degrees(acosf(value)));
	}

	Angle arctangent(float value)
	{
		return Angle(to_degrees(atanf(value)));
	}

	Angle& least(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return A;
		if (A.degree > B.degree)
			return B;
		return A;
	}

	Angle& greatest(Angle& A, Angle& B)
	{
		if (A.degree < B.degree)
			return B;
		if (A.degree > B.degree)
			return A;
		return A;
	}
}

bool operator == (Angle A, Angle B)
{
	return A.degree == B.degree;
}

bool operator == (Angle A, float degree)
{
	return A.degree == degree;
}

bool operator != (Angle A, Angle B)
{
	return A.degree != B.degree;
}

bool operator != (Angle A, float degree)
{
	return A.degree != degree;
}

bool operator < (Angle A, Angle B)
{
	return A.degree < B.degree;
}

bool operator < (Angle A, float degree)
{
	return A.degree < degree;
}

bool operator <= (Angle A, Angle B)
{
	return A.degree <= B.degree;
}

bool operator <= (Angle A, float degree)
{
	return A.degree <= degree;
}

bool operator > (Angle A, Angle B)
{
	return A.degree > B.degree;
}

bool operator > (Angle A, float degree)
{
	return A.degree > degree;
}

bool operator >= (Angle A, Angle B)
{
	return A.degree >= B.degree;
}

bool operator >= (Angle A, float degree)
{
	return A.degree >= degree;
}

strong_ordering operator <=> (Angle A, Angle B)
{
	if (A.degree < B.degree)
		return strong_ordering::less;
	if (A.degree > B.degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

strong_ordering operator <=> (Angle A, float degree)
{
	if (A.degree < degree)
		return strong_ordering::less;
	if (A.degree > degree)
		return strong_ordering::greater;
	return strong_ordering::equivalent;
}

Angle operator - (Angle A)
{
	return Angle(-A.degree);
}

Angle operator + (Angle A, Angle B)
{
	return Angle(A.degree + B.degree);
}

Angle operator + (Angle A, float degree)
{
	return Angle(A.degree + degree);
}

Angle operator - (Angle A, Angle B)
{
	return Angle(A.degree - B.degree);
}

Angle operator - (Angle A, float degree)
{
	return Angle(A.degree - degree);
}

Angle operator * (Angle A, float scalar)
{
	return Angle(A.degree * scalar);
}

Angle operator / (Angle A, float scalar)
{
	return Angle(A.degree / scalar);
}

Angle& operator += (Angle& A, Angle B)
{
	A.degree += B.degree;
	return A;
}

Angle& operator += (Angle& A, float degree)
{
	A.degree += degree;
	return A;
}

Angle& operator -= (Angle& A, Angle B)
{
	A.degree -= B.degree;
	return A;
}

Angle& operator -= (Angle& A, float degree)
{
	A.degree -= degree;
	return A;
}

Angle& operator *= (Angle& A, float scalar)
{
	A.degree *= scalar;
	return A;
}

Angle& operator /= (Angle& A, float scalar)
{
	A.degree /= scalar;
	return A;
}

ostream& operator << (ostream& os, Angle A)
{
	os << A.toString();
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Joystick::Joystick()
	{
		xDeadzone = 0.1f;
		yDeadzone = 0.1f;
	}

	Joystick::Joystick(float X, float Y, float x_dz, float y_dz)
	{
		position.set(X, Y);
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	Joystick::Joystick(const Vector2f& Position, float x_dz, float y_dz)
	{
		position = Position;
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	void Joystick::setHorizontalDeadzone(float x_dz)
	{
		xDeadzone = x_dz;
	}

	void Joystick::setVerticalDeadzone(float y_dz)
	{
		yDeadzone = y_dz;
	}

	void Joystick::setDeadzones(float x_dz, float y_dz)
	{
		xDeadzone = x_dz;
		yDeadzone = y_dz;
	}

	bool Joystick::isStickInDeadZone() const
	{
		return (fabsf(position.x) <= xDeadzone) && (fabsf(position.y) <= yDeadzone);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Gamepad::Gamepad()
	{
		leftTrigger = 0.0f;
		rightTrigger = 0.0f;
	}

	Gamepad::Gamepad(u8 Port, float lx_dz, float ly_dz, float rx_dz, float ry_dz)
	{
		_port = Port;
		leftTrigger = 0.0f;
		rightTrigger = 0.0f;
		leftStick.xDeadzone = lx_dz;
		leftStick.yDeadzone = ly_dz;
		rightStick.xDeadzone = rx_dz;
		rightStick.yDeadzone = ry_dz;
	}

	bool Gamepad::isConnected()
	{
		ZeroMemory(&_state, sizeof(XINPUT_STATE));
		DWORD result = XInputGetState(_port + 1, &_state);

		return result == ERROR_SUCCESS;
	}

	u8 Gamepad::getPort() const
	{
		return _port + 1;
	}

	XINPUT_STATE Gamepad::getState() const
	{
		return _state;
	}

	void Gamepad::update()
	{
		// Update the Gamepad State.
		ZeroMemory(&_state, sizeof(XINPUT_STATE));
		XInputGetState(_port + 1, &_state);

		// Update the left and right joysticks.
		leftStick.position.x = static_cast<float>(_state.Gamepad.sThumbLX) / 32768.0f + 0.0000155f;
		leftStick.position.y = static_cast<float>(_state.Gamepad.sThumbLY) / 32768.0f + 0.0000155f;
		rightStick.position.x = static_cast<float>(_state.Gamepad.sThumbRX) / 32768.0f + 0.0000155f;
		rightStick.position.y = static_cast<float>(_state.Gamepad.sThumbRY) / 32768.0f + 0.0000155f;

		// Update the left and right triggers.
		leftTrigger = _state.Gamepad.bLeftTrigger / 255.0f;
		rightTrigger = _state.Gamepad.bRightTrigger / 255.0f;
	}

	bool Gamepad::isButtonPressed(Button button) const
	{
		return _state.Gamepad.wButtons & button;
	}
}

bool operator == (const Gamepad& A, const Gamepad& B)
{
	return A.getPort() == B.getPort();
}

bool operator != (const Gamepad& A, const Gamepad& B)
{
	return A.getPort() != B.getPort();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	const Duration jlib::TimeZero = Duration(0.f);

	Clock::Clock()
	{
		_start = now();
	}

	TimePoint Clock::startTime() const
	{
		return _start;
	}

	TimePoint Clock::now() const
	{
		return system_clock::now();
	}

	Duration Clock::restart()
	{
		TimePoint time(now());
		Duration time_elapsed(time - _start);
		_start = time;
		return time_elapsed;
	}

	Duration Clock::timeElapsed() const
	{
		return now() - _start;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace jlib
{
	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color::Color(u8 R, u8 G, u8 B, u8 A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}

	Color::Color(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	Color::Color(const FixedArray<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	Color::Color(initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);
	}

	Color::Color(const sf::Color& other)
	{
		r = other.g;
		g = other.g;
		b = other.b;
		a = other.a;
	}

	Color& Color::operator = (u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;

		return *this;
	}

	Color& Color::operator = (const FixedArray<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];

		return *this;
	}

	Color& Color::operator = (initializer_list<u8> list)
	{
		r = *(list.begin() + 0);
		g = *(list.begin() + 1);
		b = *(list.begin() + 2);
		a = *(list.begin() + 3);

		return *this;
	}

	Color& Color::operator = (const sf::Color& other)
	{
		r = other.g;
		g = other.g;
		b = other.b;
		a = other.a;

		return *this;
	}

	void Color::set(u8 R, u8 G, u8 B, u8 A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}

	void Color::set(u32 color)
	{
		r = (color & 0xff000000) >> 24;
		g = (color & 0x00ff0000) >> 16;
		b = (color & 0x0000ff00) >> 8;
		a = (color & 0x000000ff) >> 0;
	}

	void Color::set(const FixedArray<u8, 4>& arr)
	{
		r = arr[0];
		g = arr[1];
		b = arr[2];
		a = arr[3];
	}

	u32 Color::toInt() const
	{
		return (r << 24) | (g << 16) | (b << 8) | a;
	}

	FixedArray<u8, 4> Color::toArray() const
	{
		return FixedArray<u8, 4>{ r, g, b, a };
	}

	sf::Color Color::toSFML() const
	{
		return sf::Color(r, g, b, a);
	}

	string Color::toString() const
	{
		string str;
		str.reserve(8);
		str += to_hex_str(r);
		str += to_hex_str(g);
		str += to_hex_str(b);
		str += to_hex_str(a);
		return str;
	}

	FixedArray<u8, 4> to_bytes(u32 i)
	{
		FixedArray<u8, 4> bytes;

		bytes[0] = (i & 0xff000000) >> 24;
		bytes[1] = (i & 0x00ff0000) >> 16;
		bytes[2] = (i & 0x0000ff00) >> 8;
		bytes[3] = (i & 0x000000ff) >> 0;

		return bytes;
	}

	string to_hex_str(u8 cbyte)
	{
		string hexstr("00");

		for (u8 i = 0; i < 2; ++i)
		{
			switch (cbyte % 16)
			{
				case 10: hexstr[1 - i] = 'a';               break;
				case 11: hexstr[1 - i] = 'b';               break;
				case 12: hexstr[1 - i] = 'c';               break;
				case 13: hexstr[1 - i] = 'd';               break;
				case 14: hexstr[1 - i] = 'e';               break;
				case 15: hexstr[1 - i] = 'f';               break;
				default: hexstr[1 - i] = (cbyte % 16) + 48; break;
			}

			cbyte /= 16;
		}

		return hexstr;
	}

	void copy_color_data(const Color* src, u8* dst, size_t bytes)
	{
		const u8* ptr = reinterpret_cast<const u8*>(src);
		memcpy(dst, ptr, bytes);
	}
}

bool operator == (const Color& A, const Color& B)
{
	return (A.r == B.r) && (A.g == B.g) && (A.b == B.b) && (A.a == B.a);
}

bool operator != (const Color& A, const Color& B)
{
	return (A.r != B.r) && (A.g != B.g) && (A.b != B.b) && (A.a != B.a);
}

Color operator + (const Color& A, const Color& B)
{
	int r = clamp_of(int(A.r) + int(B.r), 0, 255);
	int g = clamp_of(int(A.g) + int(B.g), 0, 255);
	int b = clamp_of(int(A.b) + int(B.b), 0, 255);
	int a = clamp_of(int(A.a) + int(B.a), 0, 255);

	return Color(r, g, b, a);
}

Color operator - (const Color& A, const Color& B)
{
	int r = clamp_of(int(A.r) - int(B.r), 0, 255);
	int g = clamp_of(int(A.g) - int(B.g), 0, 255);
	int b = clamp_of(int(A.b) - int(B.b), 0, 255);
	int a = clamp_of(int(A.a) - int(B.a), 0, 255);

	return Color(r, g, b, a);
}

Color& operator += (Color& A, const Color& B)
{
	A.r = u8(clamp_of(int(A.r) + int(B.r), 0, 255));
	A.g = u8(clamp_of(int(A.g) + int(B.g), 0, 255));
	A.b = u8(clamp_of(int(A.b) + int(B.b), 0, 255));
	A.a = u8(clamp_of(int(A.a) + int(B.a), 0, 255));

	return A;
}

Color& operator -= (Color& A, const Color& B)
{
	A.r = u8(clamp_of(int(A.r) - int(B.r), 0, 255));
	A.g = u8(clamp_of(int(A.g) - int(B.g), 0, 255));
	A.b = u8(clamp_of(int(A.b) - int(B.b), 0, 255));
	A.a = u8(clamp_of(int(A.a) - int(B.a), 0, 255));

	return A;
}

Color operator * (const Color& A, float f)
{
	float r = clamp_of(A.r * f, 0.0f, 255.0f);
	float g = clamp_of(A.g * f, 0.0f, 255.0f);
	float b = clamp_of(A.b * f, 0.0f, 255.0f);
	float a = clamp_of(A.a * f, 0.0f, 255.0f);

	return Color(r, g, b, a);
}

Color operator / (const Color& A, float f)
{
	float r = clamp_of(A.r / f, 0.0f, 255.0f);
	float g = clamp_of(A.g / f, 0.0f, 255.0f);
	float b = clamp_of(A.b / f, 0.0f, 255.0f);
	float a = clamp_of(A.a / f, 0.0f, 255.0f);

	return Color(r, g, b, a);
}

Color& operator *= (Color& A, float f)
{
	A.r = u8(clamp_of(A.r * f, 0.0f, 255.0f));
	A.g = u8(clamp_of(A.g * f, 0.0f, 255.0f));
	A.b = u8(clamp_of(A.b * f, 0.0f, 255.0f));
	A.a = u8(clamp_of(A.a * f, 0.0f, 255.0f));

	return A;
}

Color& operator /= (Color& A, float f)
{
	A.r = u8(clamp_of(A.r / f, 0.0f, 255.0f));
	A.g = u8(clamp_of(A.g / f, 0.0f, 255.0f));
	A.b = u8(clamp_of(A.b / f, 0.0f, 255.0f));
	A.a = u8(clamp_of(A.a / f, 0.0f, 255.0f));

	return A;
}

ostream& operator << (ostream& os, const Color& A)
{
	os << A.toString();
	return os;
}