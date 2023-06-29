#include"event.hpp"

#include"ymemory.hpp"
#include"containers/vector.hpp"

namespace Yazh::Event {
	using RegisteredEvent = struct RegisteredEvent {
		Listener* listener;
		onEvent_ptr callback;
	};
	
	using CodeEntry = struct CodeEntry {
		Yazh::Containers::Vector<RegisteredEvent> events;
	};
	
	// This should be more than enough codes...
#define MAX_CODES 65536
	
	using SystemState = struct SystemState {
		// lookup table for event codes.
		CodeEntry registered[MAX_CODES];
	};
	
	/**
	 * Event system internal state.
	 */
	static bool isInitialized = false;
	static SystemState state;
	
	bool initialize() {
		if (isInitialized) return false;
		isInitialized = false;
		for (auto code : state.registered)
			code.events.clear();
		
		isInitialized = true;
		
		return true;
	}
	
	void shutdown() {
		// free the events arrays. And objects pointed to should be destroyed on their own.
		for (auto code : state.registered) {
			delete &code.events;
		}
	}
	
	bool Register(u16 code, Listener* listener, onEvent_ptr onEvent) {
		if (!isInitialized) return false;
		
		for (auto e : state.registered[code].events) {
			if (e.listener == listener) {
				/* TODO (#1#): warn */
				return false;
			}
		}
		
		// if in this point no duplicate was found. Proceed with registration.
		RegisteredEvent event;
		event.listener = listener;
		event.callback = onEvent;
		state.registered[code].events.push(event);
		
		return true;
	}
	
	bool Unregister(u16 code, Listener* listener, onEvent_ptr onEvent) {
		if (!isInitialized)
			return false;
		
		for (u64 i = 0; i < state.registered[code].events.size(); i++) {
			auto e = state.registered[code].events[i];
			if (e.listener == listener && e.callback == onEvent) {
				// Found one, remove it
				state.registered[code].events.pop(i);
				return true;
			};
		}
		
		// Not found.
		return false;
	}
	
	bool Fire(u16 code, Sender* sender, context data) {
		if(isInitialized)
			return false;
			
		for(auto e : state.registered[code].events) {
			if(e.callback(code, sender, e.listener, data)) {
				// Message has been handled, do not send to other listeners.
				return true;
			}
		}
		
		// Not found
		return false;
	}
} // namespace Yazh::Event