#pragma once

#include"defines.hpp"

namespace Yazh::Input {
	using Button = enum class Button {
		Left,
		Middle,
		Right,
		
		MAX,
	};

	using Key = enum class Key {
		Backspace = 0X8,
		Enter = 0XD,
		Tab = 0X9,
		Shift = 0X10,
		Ctrl = 0X11,

		Pause = 0X13,
		CapsLock = 0X14,

		Esc = 0X1B,

		Convert = 0X1C,
		NowConvert = 0X1D,
		Accept = 0X1E,
		ModeChange = 0X1F,

		Space = 0X20,
		Prior = 0X21,
		Next = 0X22,
		End = 0X23,
		Home = 0X24,
		Left = 0X25,
		Up = 0X26,
		Right = 0X27,
		Down = 0X28,
		Select = 0X29,
		Print = 0X2A,
		Execute = 0X2B,
		Snapshot = 0X2C,
		Insert = 0X2D,
		Delete = 0X2E,
		Help = 0X2F,

		A = 0X41,
		B = 0X42,
		C = 0X43,
		D = 0X44,
		E = 0X45,
		F = 0X46,
		G = 0X47,
		H = 0X48,
		I = 0X49,
		J = 0X4A,
		K = 0X4B,
		L = 0X4C,
		M = 0X4D,
		N = 0X4E,
		O = 0X4F,
		P = 0X50,
		Q = 0X51,
		R = 0X52,
		S = 0X53,
		T = 0X54,
		U = 0X55,
		V = 0X56,
		W = 0X57,
		X = 0X58,
		Y = 0X59,
		Z = 0X5A,

		LWin = 0X5B,
		MWin = 0X5C,
		Apps = 0X5D,

		Sleep = 0X5F,

		NumPad0 = 0X60,
		NumPad1 = 0X61,
		NumPad2 = 0X62,
		NumPad3 = 0X63,
		NumPad4 = 0X64,
		NumPad5 = 0X65,
		NumPad6 = 0X66,
		NumPad7 = 0X67,
		NumPad8 = 0X68,
		NumPad9 = 0X69,
		Multiply = 0X6A,
		Add = 0X6B,
		Separator = 0X6C,
		Subtract = 0X6D,
		Decimal = 0X6E,
		Divide = 0X6F,
		F1 = 0X70,
		F2 = 0X71,
		F3 = 0X72,
		F4 = 0X73,
		F5 = 0X74,
		F6 = 0X75,
		F7 = 0X76,
		F8 = 0X77,
		F9 = 0X78,
		F10 = 0X79,
		F11 = 0X7A,
		F12 = 0X7B,
		F13 = 0X7C,
		F14 = 0X7D,
		F15 = 0X7E,
		F16 = 0X7F,
		F17 = 0X80,
		F18 = 0X81,
		F19 = 0X82,
		F20 = 0X83,
		F21 = 0X84,
		F22 = 0X85,
		F23 = 0X86,
		F24 = 0X87,

		NumLock = 0X90,
		Scroll = 0X91,

		NumPadEqual = 0X92,
		LShift = 0XA0,
		RShift = 0XA1,
		LCtrl = 0XA2,
		Rctrl = 0XA3,
		LMenu = 0XA4,
		RMenu = 0XA5,

		Semicolon = 0XBA,
		Plus = 0XBB,
		Comma = 0XBC,
		Minus = 0XBD,
		Period = 0XBE,
		Slash = 0XBF,
		Grave = 0XC0,
	};
#define MAX_KEYS 0x100

	void initialize();
	void shutdown();
	void update(f64);

	// keyboard input
	YAPI bool isDown(Key);
	YAPI bool isUp(Key);
	YAPI bool wasDown(Key);
	YAPI bool wasUp(Key);

	void process(Key, bool); // key

	// mouse input
	YAPI bool isDown(Button);
	YAPI bool isUp(Button);
	YAPI bool wasDown(Button);
	YAPI bool wasUp(Button);
	YAPI void getMousePosition(i32*, i32*);
	YAPI void getPreviousMousePosition(i32*, i32*);

	void process(Button, bool); // button
	void process(i16, i16); // mouse move
	void process(i8); // mouse wheel
}; // namespace Yazh::Input