#include"input.hpp"
#include"event.hpp"
#include"ymemory.hpp"
#include"logger.hpp"
#include<map>

namespace Yazh::Input {
	using KeyboardState = struct KeyboardState {
		bool Keys[MAX_KEYS];
	};

	using MouseState = struct MouseState {
		i16 x;
		i16 y;
		std::map<Button, bool> Buttons;
	};

	using State = struct State {
		KeyboardState keyboard_now;
		KeyboardState keyboard_then;
		MouseState mouse_now;
		MouseState mouse_then;
	};

	// Internal input state.
	static auto initialized = false;
	static State state = {};

	void initialize() {
		Yazh::Memory::zero(&state.keyboard_now, sizeof(KeyboardState));
		Yazh::Memory::zero(&state.keyboard_now, sizeof(KeyboardState));
		state.mouse_now.x = 0;
		state.mouse_now.y = 0;
		for (auto i = 0; i < (u16)Button::MAX; i++) {
			state.mouse_now.Buttons[(Button)i] = false;
			state.mouse_then.Buttons[(Button)i] = false;
		}
		initialized = true;
		YINFO("Input subsystem initialized.");
	}

	void shutdown() {
		// TODO: Add shutdown routines when needed.
		initialized = false;
	}

	void update(f64 deltaTime) {
		if (!initialized)
			return;

		// Copy current states to previous states.
		Yazh::Memory::copy(&state.keyboard_then, &state.keyboard_now, sizeof(KeyboardState));
		Yazh::Memory::copy(&state.mouse_then, &state.mouse_now, sizeof(MouseState));
	}

	void process(Key key, bool pressed) {
		// Only handle this if the state actually changed.
		if (state.keyboard_now.Keys[(u16)key] != pressed) {
			// Update internal state.
			state.keyboard_now.Keys[(u16)key] = pressed;

			// Fire off an event for immediate processing.
			Yazh::Event::Context context;
			context.data.U16[0] = (u16)key;
			Yazh::Event::Fire(pressed ? (u16)Yazh::Event::SystemCode::KeyPressed : (u16)Yazh::Event::SystemCode::KeyReleased, nullptr, context);
		}
	}
	void process(Button button, bool pressed) {
		// Only handle this if the state actually changed.
		if (state.mouse_now.Buttons[button] != pressed) {
			state.mouse_now.Buttons[button] = pressed;

			// Fire the event.
			Yazh::Event::Context context;
			context.data.U16[0] = (u16)button;
			Yazh::Event::Fire(pressed ? (u16)Yazh::Event::SystemCode::ButtonPressed : (u16)Yazh::Event::SystemCode::ButtonReleased, nullptr, context);
		}
	}
	void process(i16 x, i16 y) {
		// Only process if actually different.
		if (state.mouse_now.x != x || state.mouse_now.y != y) {
			// NOTE: Enable this if debugging.
			// YDEBUG("Mouse pos: ", x, ", ", y);

			// Update internal state.
			state.mouse_now.x = x;
			state.mouse_now.y = y;

			// Fire the event.
			Yazh::Event::Context context;
			context.data.U16[0] = x;
			context.data.U16[1] = y;
			Yazh::Event::Fire((u16)Yazh::Event::SystemCode::MouseMoved, nullptr, context);
		}
	}
	void process(i8 zDelta) {
		// NOTE: no internal state to update.

		// Fire the event.
		Yazh::Event::Context context;
		context.data.U8[0] = zDelta;
		Yazh::Event::Fire((u16)Yazh::Event::SystemCode::MouseWheel, nullptr, context);
	}

	bool isDown(Key key) {
		if (!initialized)
			return false;
		return state.keyboard_now.Keys[(u16)key] == true;
	}
	bool isUp(Key key) {
		if (!initialized)
			return true;
		return state.keyboard_now.Keys[(u16)key] == false;
	}
	bool wasDown(Key key) {
		if (!initialized)
			return false;
		return state.keyboard_then.Keys[(u16)key] == true;
	}
	bool wasUp(Key key) {
		if (!initialized)
			return true;
		return state.keyboard_then.Keys[(u16)key] == false;
	}

	bool isDown(Button button) {
		if (!initialized)
			return false;
		return state.mouse_now.Buttons[button] == true;
	}
	bool isUp(Button button) {
		if (!initialized)
			return true;
		return state.mouse_now.Buttons[button] == false;
	}
	bool wasDown(Button button) {
		if (!initialized)
			return false;
		return state.mouse_then.Buttons[button] == true;
	}
	bool wasUp(Button button) {
		if (!initialized)
			return true;
		return state.mouse_then.Buttons[button] == false;
	}

	void getMousePosition(i32* x, i32* y) {
		if(!initialized) {
			*x = 0;
			*y = 0;
			return;
		}
		*x = state.mouse_now.x;
		*y = state.mouse_now.y;
	}
	void getPreviousMousePosition(i32* x, i32* y) {
		if(!initialized) {
			*x = 0;
			*y = 0;
			return;
		}
		*x = state.mouse_then.x;
		*y = state.mouse_then.y;
	}
} // namespace Yazh::input