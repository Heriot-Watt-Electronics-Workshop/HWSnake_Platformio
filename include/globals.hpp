#ifndef __GLOBALS_HPP_

#include <Arduino.h>
#include "Geometry.hpp"

// Defined for readability.
#define YES 1
#define NO 0

// This switches on or off serial debug output.
#define DEBUG NO // or NO
#define LIVE_ERRORS NO

// Write yes to remove the high score.
#define CLEAR_HIGH_SCORE NO

// This determines the size of the array used to store the snake.  The
// snake may be 4 times this size + 1 for the head.  Maximum if all spaces 
// were in the snake would be 160 sections so 40 bytes of data should be enough.
#if (DEBUG == YES)
constexpr uint8_t SNAKE_DATA_SIZE { 4 };
#elif (DEBUG == NO)
constexpr uint8_t SNAKE_DATA_SIZE { 40 };
#endif

// Store Points as a pair of this type.
// int8_t will give a range of -127 to +128.
// uint8_t will give a range of 0 to 255.
using POINT_DATA_TYPE = uint8_t;
using PointType = Point<POINT_DATA_TYPE>;
using SizeType = PointType;
using Rect = Rectangle<PointType>;


// If you want sound. U will need a buzzer.
#define SOUND NO
#if (SOUND == 0)
	#define tone(x, y, z)
#endif


// This makes all debugging print statements disappear when DEBUG set to NO.
#if (DEBUG == YES)
	#include "string.h"
	#define DEBUG_PRINT_FLASH(x) 	Serial.print(F(x))
	#define DEBUG_PRINTLN_FLASH(x) 	Serial.println(F(x))
	#define DEBUG_PRINT(x) 			Serial.print(x)
	#define DEBUG_PRINTLN(x) 		Serial.println(x)
	#define DEBUG_PRINT_HEX(x) 		Serial.print(x, HEX)
	#define DEBUG_PRINTLN_HEX(x) 	Serial.println(x, HEX)
#else
	#define DEBUG_PRINT_FLASH(x)
	#define DEBUG_PRINTLN_FLASH(x)
	#define DEBUG_PRINT(x)
	#define DEBUG_PRINTLN(x)
	#define DEBUG_PRINT_HEX(x)
	#define DEBUG_PRINTLN_HEX(x)
#endif // DEBUG


namespace Utility {

// #if (DEBUG == YES)
// // This class allows to print any integer type in binary format.
// //  It is here to aid in debugging. 
// template<typename T>
// struct Binary : public Printable {
//     T value;
// 	constexpr Binary(T value) : value{value} { } 
// 	size_t printTo(Print& p) const;
// };
// #endif // (DEBUG == YES)

}


// The pin numbers.
namespace Pin {

	constexpr uint8_t UP 	{ 7 };
	constexpr uint8_t DOWN 	{ 8 };
	constexpr uint8_t LEFT 	{ 4 };
	constexpr uint8_t RIGHT { 2 };
	constexpr uint8_t MIDDLE{ 3 };

#if (SOUND == YES)
	constexpr uint8_t SOUND { 9 };
#endif
}

namespace Display {
	constexpr uint8_t Address 	{ 0x3C };
	constexpr Rect dspRect {{64, 128}};
}


namespace World {

	// How large in pixels do you want the game rows and columns to be.
	constexpr uint8_t Scale { 6 };

	// Offsets top left and right.
	constexpr uint8_t xMinOffset { 4 };
	constexpr uint8_t xMaxOffset { 2 };
	constexpr uint8_t yMinOffset { 12 };
	constexpr uint8_t yMaxOffset { 2 };

	// How big the world is.
	constexpr Rect World {
			0,																	// minY
			0,																	// minX
			(Display::dspRect.height() - yMinOffset - yMaxOffset) / Scale,		// maxY
			(Display::dspRect.width() - xMinOffset - xMaxOffset) / Scale 		// maxX
	};
}


// All the directions you need.
// First 4 directions are reversible if bits are reversed.
// Middle is for middle button.
// ie UP is 0b00 and down is 0b11.
enum class Direction : uint8_t {
    UP = 0, LEFT, RIGHT, DOWN, NONE, MIDDLE
};

// Flipping the bits reverses the Direction.
Direction operator~(const Direction direction);

// #if (DEBUG == YES)
// String DirectionAsString(const Direction d);
// #endif // (DEBUG == YES)


// Template function definitions are defined in the header.

namespace Utility {

//#if (DEBUG == YES)
// template<typename T>
// size_t Binary<T>::printTo(Print& p) const {

// 	char binStr[sizeof(T) + 2];
// 	T b { this->value };
// 	T rev {0};

//     for (uint16_t i{}; i < static_cast<uint16_t>(sizeof(T)) * 8; ++i) {
//         rev = rev << 1;
//         rev += (b % 2);
//         b = b >> 1;
//     }
//     for (uint16_t i{}; i < static_cast<uint16_t>(sizeof(T)) * 8; ++i) {
//     	binStr[i] = (rev % 2);
//         rev = rev >> 1;
//     }
// 	return p.print(binStr);
// }
// #endif // (DEBUG == YES)
}

#define __GLOBALS_HPP_
#endif // __GLOBALS_HPP_
