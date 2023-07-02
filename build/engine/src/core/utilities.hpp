#pragma once

#include"defines.hpp"

namespace Yazh::Utilities {
    f64 getAbsoluteTime();
			
    // Sleep on the thread for the provided ms. This blocks the main thread.
    // Should only be used for giving time back to the OS for unused update power.
    // Therefore it is not exported.
    void sleep(f64 ms);
}