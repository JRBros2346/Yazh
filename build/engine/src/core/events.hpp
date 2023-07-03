#pragma once

#include"defines.hpp"

namespace Yazh::Events {
    // Forward declarations.
    class Sender;
    class Listener;
    using Context = struct Context {
        // 128 bytes
        union {
            i64 I64[2];
            u64 U64[2];
            f64 F64[2];

            i32 I32[4];
            u32 U32[4];
            f32 F32[4];

            i16 I16[8];
            u16 U16[8];

            i8 I8[16];
            u8 U8[16];
            char C[16];
        } data;
    };

    // Should return true if handled.
    using onEvent = bool (*)(u16, Sender* sender, Listener* listenerInst, Context);

    bool initialize();
    void shutdown();
        /**
     * Register to listen for when events are sent with the provided code. Events with duplicate
     * listener/callback combos will not be registered again and will cause this to return FALSE.
     * @param code The event code to listen for.
     * @param listener A pointer to a listener instance. Can be 0/NULL.
     * @param on_event The callback function pointer to be invoked when the event code is fired.
     * @returns TRUE if the event is successfully registered; otherwise false.
     */
    YAPI bool Register(u16 code, Listener* listener, onEvent on_event);

    /**
     * Unregister from listening for when events are sent with the provided code. If no matching
     * registration is found, this function returns FALSE.
     * @param code The event code to stop listening for.
     * @param listener A pointer to a listener instance. Can be 0/NULL.
     * @param on_event The callback function pointer to be unregistered.
     * @returns TRUE if the event is successfully unregistered; otherwise false.
     */
    YAPI bool Unregister(u16 code, void* listener, onEvent on_event);

    /**
     * Fires an event to listeners of the given code. If an event handler returns 
     * TRUE, the event is considered handled and is not passed on to any more listeners.
     * @param code The event code to fire.
     * @param sender A pointer to the sender. Can be 0/NULL.
     * @param data The event data.
     * @returns TRUE if handled, otherwise FALSE.
     */
    YAPI bool Fire(u16 code, void* sender, Context data);

    // System internal event codes. Application should use codes beyond 255.
    using SystemCode = enum class SystemCode {
        // Shuts the application down on the next frame.
        ApplicationQuit = 0x01,

        // Keyboard key pressed.
        /* Context usage:
         * u16 keyCode = data.data.U16[0];
         */
        KeyPressed = 0x02,

        // Keyboard key released.
        /* Context usage:
         * u16 keyCode = data.data.U16[0];
         */
        KeyReleased = 0x03,

        // Mouse button pressed.
        /* Context usage:
         * u16 button = data.data.U16[0];
         */
        ButtonPressed = 0x04,

        // Mouse button released.
        /* Context usage:
         * u16 button = data.data.U16[0];
         */
        ButtonReleased = 0x05,

        // Mouse moved.
        /* Context usage:
         * u16 x = data.data.U16[0];
         * u16 y = data.data.U16[1];
         */
        MouseMoved = 0x06,

        // Mouse moved.
        /* Context usage:
         * u8 deltaZ = data.data.U8[0];
         */
        MouseWheel = 0x07,

        // Resized/resolution changed from the OS.
        /* Context usage:
         * u16 width = data.data.U16[0];
         * u16 height = data.data.U16[1];
         */
        Resized = 0x08,

        MAX = 0xFF
    };
}
