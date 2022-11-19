#include<core/logger.hpp>
#include<core/asserts.hpp>

int main(void) {
    YFATAL("A test message: ",3.14f);
    YERROR("A test message: ",3.14f);
    YWARN("A test message: ",3.14f);
    YINFO("A test message: ",3.14f);
    YDEBUG("A test message: ",3.14f);
    YTRACE("A test message: ",3.14f);
    
    Yazh::Platfrom platform();
    if (platform.startup(&state, "Yazh Engine Testbed", 100, 100, 1280, 720)) {
    	while (true) {
    		platform.pumpMessages(&state)
		}
	}
	platform.shutdown();
}