#include<core/logger.hpp>
#include<core/asserts.hpp>
#include<platform/platform_win32.cpp>

int main(void) {
    YFATAL("A test message: ",3.14f);
    YERROR("A test message: ",3.14f);
    YWARN("A test message: ",3.14f);
    YINFO("A test message: ",3.14f);
    YDEBUG("A test message: ",3.14f);
    YTRACE("A test message: ",3.14f);
    
    Yazh::Platform platform();
    if (platform.startup("Yazh Engine Testbed", 100, 100, 1280, 720)) {
    	while (true) {
    		platform.pumpMessages()
		}
	}
	platform.shutdown();
}