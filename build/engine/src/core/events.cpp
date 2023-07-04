#include"events.hpp"

#include"types/vector.hpp"
#include"ymemory.hpp"

namespace Yazh::Events {
	using RegisteredEvent = struct RegisteredEvent {
		Listener* listener;
		OnEvent callback;
	};

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 65536

	/**
	 * Event system internal state.
	 */
	static auto isInitialized = false;
	// lookup table for event code.
	static Yazh::Types::Vector<RegisteredEvent> state[MAX_MESSAGE_CODES];

	bool initialize() {
		if (isInitialized)
			return false;
		isInitialized = false;
		for (auto codeEntry : state)
			for (u64 i = 0; i < codeEntry.size(); i++)
				Yazh::Memory::zero(&codeEntry[i], sizeof(RegisteredEvent));

		isInitialized = true;
		return true;
	}

	void event_shutdown() {
		// Free the events arrays. And objects pointed to should be destroyed on their own.
		for(auto codeEntry : state)
			if(codeEntry.size() != 0)
				delete &codeEntry;
	}

	bool Register(u16 code, Listener* listener, OnEvent on_event) {
		if(!isInitialized)
			return false;

		for(u64 i = 0; i < state[code].size(); i++) {
			if(state[code][i].listener == listener) {
				// TODO: warn
				return false;
			}
		}

		// If at this point, no duplicate was found. Proceed with registration.
		RegisteredEvent event;
		event.listener = listener;
		event.callback = on_event;
		state[code].push(event);

		return true;
	}

	bool Unregister(u16 code, Listener* listener, OnEvent on_event) {
		if(!isInitialized) {
			return false;
		}

		// On nothing is registered for the code, boot out.
		if(state[code].size() == 0) {
			// TODO: warn
			return false;
		}

		for(u64 i = 0; i < state[code].size(); i++) {
			RegisteredEvent e = state[code][i];
			if(e.listener == listener && e.callback == on_event) {
				// Found one, remove it
				state[code].pop(i);
				return true;
			}
		}

		// Not found.
		return false;
	}

	bool Fire(u16 code, Sender* sender, Context data) {
		if(!isInitialized)
			return false;

		// If nothing is registered for the code, boot out.
		if(state[code].size() == 0) {
			return false;
		}

		for(u64 i = 0; i < state[code].size(); i++) {
			RegisteredEvent e = state[code][i];
			if(e.callback(code, sender, e.listener, data)) {
				// Message has been handled, do not send to other listeners.
				return true;
			}
		}

		// Not found.
		return false;
	}
}