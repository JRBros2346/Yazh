// Linux Platform Layer
#if YPLATFORM_LINUX
#	include"platform_linux.hpp"

#	include"core/logger.hpp"

#	include<cstdlib>
#	include<cstring>

namespace Yazh {
	bool Platform::startup(
			const char* applicationName,
			i32 x,
			i32 y,
			i32 width,
			i32 height) {
		
		// Connect to X
		display = XOpenDisplay(NULL);
			
		// Turn off key repeats.
		XAutoRepeatOff(display);
			
		// Retrieve the connection from the display.
		connection = XGetXCBConnection(display);
		
		if (xcb_connection_has_error(connection)) {
			YFATAL("Failed to connect to X server via XCB.");
			return false;
		}

		// Get data from the X server
		const struct xcb_setup_t* setup = xcb_get_setup(connection);
		
		// Loop through screens using iterator
		auto pScreen = 0;
		xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
		for (i32 s = pScreen; s>0; s++) {
			xcb_screen_next(&it);
		}
		
		// After screens have been looped through, assign it.
		screen = it.data;
		
		// Allocate a XID for the window to be created.
		window = xcb_generate_id(connection);
		
		// Register event types.
		// XCB_CW_BACK_PIXEL = filling then window bg with a single colour
		// XCB_CW_EVENT_MASK is required.
		u32 eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		
		// Listen for keyboard and mouse buttons
		u32 eventValues = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
		                  XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
		                  XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
		                  XCB_EVENT_MASK_STRUCTURE_NOTIFY;
		
		// Values to be sent over XCB (bg colour, events)
		u32 valueList[] = {screen->black_pixel, eventValues};
		
		// Create the window
		xcb_void_cookie_t cookie = xcb_create_window(
			connection,
			XCB_COPY_FROM_PARENT,         	// depth
			window,
			screen->root,                 	// parent
			x,                            	// x
			y,                            	// y
			width,                        	// width
			height,                       	// height
			0,                            	// No Border
			XCB_WINDOW_CLASS_INPUT_OUTPUT,	// class
			screen->root_visual,
			eventMask,
			valueList);
		
		// Change the title
		xcb_change_property(
			connection,
			XCB_PROP_MODE_REPLACE,
			window,
			XCB_ATOM_WM_NAME,
			XCB_ATOM_STRING,
			8,	// data should be viewed 8 bits at a time
			strlen(applicationName),
			applicationName);
		
		/* Tell the server to notify when the window manager
		   attempts to destroy the window. */
		xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
			connection,
			0,
			strlen("wmDeleteWinDOW"),
			"wmDeleteWinDOW");
		xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(
			connection,
			0,
			strlen("wmProtocols"),
			"wmProtocols");
		xcb_intern_atom_reply_t* wmDeleteReply = xcb_intern_atom_reply(
			connection,
			wmDeleteCookie,
			NULL);
		xcb_intern_atom_reply_t* wmProtocolsReply = xcb_intern_atom_reply(
			connection,
			wmProtocolsCookie,
			NULL);
		wmDeleteWin = wmDeleteReply->atom;
		wmProtocols = wmProtocolsReply->atom;
		
		xcb_change_property(
			connection,
			XCB_PROP_MODE_REPLACE,
			window,
			wmProtocolsReply->atom,
			4,
			32,
			1,
			&wmDeleteReply->atom);
		
		// Map the window to the screen
		xcb_map_window(connection, window);
		
		// Flush the stream
		i32 streamResult = xcb_flush(connection);
		if (streamResult <= 0) {
			YFATAL("An error occurred when flushing the screen: ", streamResult);
			return false;
		}
		
		return true;
	}
	
	void Platform::shutdown() {
		// turns key repeats back on since this is global for the OS... just... wow.
		XAutoRepeatOn(display);
		
		xcb_destroy_window(connection, window);
	}
	
	bool Platform::pumpMessages() {
		xcb_generic_event_t* event;
		xcb_client_message_event_t* cm;
		
		auto quitFlagged = false;
		
		// Poll for events until null is returned.
		while (event != 0) {
			event = xcb_poll_for_event(connection);
			if (event == 0) {
				break;
			}
		
			// Input events
			switch (event->response_type & ~0x80) {
				case XCB_KEY_PRESS:
				case XCB_KEY_RELEASE:
					// Key presses and releases
					break;
				case XCB_BUTTON_PRESS:
				case XCB_BUTTON_RELEASE:
					// Mouse button presses and releases
					break;
				case XCB_MOTION_NOTIFY:
					// Mouse Movement
					break;
				
				case XCB_CONFIGURE_NOTIFY:
					// Resizing
					break;
				
				case XCB_CLIENT_MESSAGE:
					cm = (xcb_client_message_event_t*)event;
					
					// Window close
					if (cm->data.data32[0] == wmDeleteWin) {
						quitFlagged = true;
					}
					break;
				default:
					// Something else
					break;
			}
			
			::free(event);
		}
		return !quitFlagged;
	}
	void* Platform::allocate(ysize size, bool aligned) {
		return ::operator new(size);
	}

	void Platform::free(void *block, ysize size, bool aligned) {
		::operator delete(block, size);
	}

	void* Platform::zeroMemory(void *block, ysize size) {
		return memset(block, 0, size);
	}

	void* Platform::copyMemory(void *dest, const void* source, ysize size) {
		return memcpy(dest, source, size);
	}

	void* Platform::setMemory(void *dest, i32 value, ysize size) {
		return memset(dest, value, size);
	}
} // namespace Yazh

#endif // YPLATFORM_LINUX
