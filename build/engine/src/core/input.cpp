#include"input.hpp"
#include"event.hpp"
#include"ymemory.hpp"
#include"logger.hpp"

namespace Yazh::Input {
	using KeyboardState = struct KeyboardState {
		bool keys[MAX_KEYS];
	};

	using MouseState = struct MouseState {
		i16 x;
		i16 y;
		bool buttons[(u16)Button::MAX];
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
		Memory::zero(&state, sizeof(State));
		initialized = true;
		YINFO("Input subsystem initialized.");
	}

	void shutdown() {
		// TODO: Add shutdown routines when needed.
		initialized = false;
	}

	void update(f64 delta_time) {
		if (!initialized)
			return;

		// Copy current states to previous states.
		Memory::copy(&state.keyboard_then, &state.keyboard_now, sizeof(KeyboardState));
		Memory::copy(&state.mouse_then, &state.mouse_now, sizeof(MouseState));
	}

	void process(Key key, bool pressed) {
		// Only handle this if the state actually changed.
		if (state.keyboard_now.keys[(u16)key] != pressed) {
			// Update internal state.
			state.keyboard_now.keys[(u16)key] = pressed;

			// Fire off an event for immediate processing.
			Event::Context context;
			context.U16[0] = (u16)key;
			Event::Fire(pressed ? (u16)Event::SystemCode::KeyPressed : (u16)Event::SystemCode::KeyReleased, nullptr, context);
		}
	}
	void process(Button button, bool pressed) {
		// Only handle this if the state actually changed.
		if (state.mouse_now.buttons[(u16)button] != pressed) {
			state.mouse_now.buttons[(u16)button] = pressed;

			// Fire the event.
			Event::Context context;
			context.U16[0] = (u16)button;
			Event::Fire(pressed ? (u16)Event::SystemCode::ButtonPressed : (u16)Event::SystemCode::ButtonReleased, nullptr, context);
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
			Event::Context context;
			context.U16[0] = x;
			context.U16[1] = y;
			Event::Fire((u16)Event::SystemCode::MouseMoved, nullptr, context);
		}
	}
	void process(i8 z_delta) {
		// NOTE: no internal state to update.

		// Fire the event.
		Event::Context context;
		context.U8[0] = z_delta;
		Event::Fire((u16)Event::SystemCode::MouseWheel, nullptr, context);
	}

	bool isDown(Key key) {
		if (!initialized)
			return false;
		return state.keyboard_now.keys[(u16)key] == true;
	}
	bool isUp(Key key) {
		if (!initialized)
			return true;
		return state.keyboard_now.keys[(u16)key] == false;
	}
	bool wasDown(Key key) {
		if (!initialized)
			return false;
		return state.keyboard_then.keys[(u16)key] == true;
	}
	bool wasUp(Key key) {
		if (!initialized)
			return true;
		return state.keyboard_then.keys[(u16)key] == false;
	}

	bool isDown(Button button) {
		if (!initialized)
			return false;
		return state.mouse_now.buttons[(u16)button] == true;
	}
	bool isUp(Button button) {
		if (!initialized)
			return true;
		return state.mouse_now.buttons[(u16)button] == false;
	}
	bool wasDown(Button button) {
		if (!initialized)
			return false;
		return state.mouse_then.buttons[(u16)button] == true;
	}
	bool wasUp(Button button) {
		if (!initialized)
			return true;
		return state.mouse_then.buttons[(u16)button] == false;
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