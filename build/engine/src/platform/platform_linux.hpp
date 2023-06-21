#pragma once

#include"platform.hpp"
#include"defines.hpp"
#include"core/logger.hpp"

#if YPLATFORM_LINUX
#	include<xcb/xcb.h>
#	include<X11/keysym.h>
#	include<X11/XKBlib.h>  	// sudo apt-get install libx11-dev
#	include<X11/Xlib.h>
#	include<X11/Xlib-xcb.h>	// sudo apt-get install libxkbcommon-x11-dev
#	include<sys/time.h>

#	include<cstdlib>
#	include<cstring>

namespace Yazh {
	class YAPI Platform : public VirtualPlatform {
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wm_protocols;
		xcb_atom_t wm_delete_win;
		
		public:
			bool startup(
					const char* application_name,
					i32 x,
					i32 y,
					i32 width,
					i32 height) override {
				
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
				int screen_p = 0;
				xcb_screen_iterator_t it = xcb_setup_roots_iterator(setup);
				for (i32 s = screen_p; s>0; s++) {
					xcb_screen_next(&it);
				}
				
				// After screens have been looped through, assign it.
				screen = it.data;
				
				// Allocate a XID for the window to be created.
				window = xcb_generate_id(connection);
				
				// Register event types.
				// XCB_CW_BACK_PIXEL = filling then window bg with a single colour
				// XCB_CW_EVENT_MASK is required.
				u32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
				
				// Listen for keyboard and mouse buttons
				u32 event_values = XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE |
				                   XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE |
				                   XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_POINTER_MOTION |
				                   XCB_EVENT_MASK_STRUCTURE_NOTIFY;
				
				// Values to be sent over XCB (bg colour, events)
				u32 value_list[] = {screen->black_pixel, event_values};
				
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
					event_mask,
					value_list);
				
				// Change the title
				xcb_change_property(
					connection,
					XCB_PROP_MODE_REPLACE,
					window,
					XCB_ATOM_WM_NAME,
					XCB_ATOM_STRING,
					8,	// data should be viewed 8 bits at a time
					strlen(application_name),
					application_name);
				
				/* Tell the server to notify when the window manager
				   attempts to destroy the window. */
				xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(
					connection,
					0,
					strlen("WM_DELETE_WINDOW"),
					"WM_DELETE_WINDOW");
				xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(
					connection,
					0,
					strlen("WM_PROTOCOLS"),
					"WM_PROTOCOLS");
				xcb_intern_atom_reply_t* wm_delete_reply = xcb_intern_atom_reply(
					connection,
					wm_delete_cookie,
					NULL);
				xcb_intern_atom_reply_t* wm_protocols_reply = xcb_intern_atom_reply(
					connection,
					wm_protocols_cookie,
					NULL);
				wm_delete_win = wm_delete_reply->atom;
				wm_protocols = wm_protocols_reply->atom;
				
				xcb_change_property(
					connection,
					XCB_PROP_MODE_REPLACE,
					window,
					wm_protocols_reply->atom,
					4,
					32,
					1,
					&wm_delete_reply->atom);
				
				// Map the window to the screen
				xcb_map_window(connection, window);
				
				// Flush the stream
				i32 stream_result = xcb_flush(connection);
				if (stream_result <= 0) {
					YFATAL("An error occurred when flushing the screen: ", stream_result);
					return false;
				}
				
				return true;
			}
			
			void shutdown() override {
				// turns key repeats back on since this is global for the OS... just... wow.
				XAutoRepeatOn(display);
				
				xcb_destroy_window(connection, window);
			}
			
			bool pumpMessages() {
				xcb_generic_event_t* event;
				xcb_client_message_event_t* cm;
				
				bool quit_flagged = false;
				
				// Poll for events until null is returned.
				while (event != 0) {
					event = xcb_poll_for_event(connection);
					if (event == 0) {
						break;
					}
				
					// Input events
					switch (event->response_type & ~0x80) {
						case XCB_KEY_PRESS:
						case XCB_KEY_RELEASE: {
							// Key presses and releases
						} break;
						case XCB_BUTTON_PRESS:
						case XCB_BUTTON_RELEASE: {
							// Mouse button presses and releases
						} break;
						case XCB_MOTION_NOTIFY:
							// Mouse Movement
							break;
						
						case XCB_CONFIGURE_NOTIFY: {
							// Resizing
						}
						
						case XCB_CLIENT_MESSAGE: {
							cm = (xcb_client_message_event_t*)event;
							
							// Window close
							if (cm->data.data32[0] == wm_delete_win) {
								quit_flagged = true;
							}
						} break;
						default:
							// Something else
							break;
					}
					
					::free(event);
				}
				return !quit_flagged;
			}
			
			static void* allocate(u64 size, bool aligned);
			static void free(void* block, bool aligned);
			static void* zeroMemory(void* block, u64 size);
			static void* copyMemory(void* dest, const void* source, u64 size);
			static void* setMemory(void* dest, i32 value, u64 size);
				
			static f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			static void sleep(u64 ms);
	};
} // namespace Yazh

#endif // YPLATFORM_LINUX