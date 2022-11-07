#include<core/logger.h>

int main(void) {
    YFATAL("A test message: ",3.14f);
    YERROR("A test message: ",3.14f);
    YWARN("A test message: ",3.14f);
    YINFO("A test message: ",3.14f);
    YDEBUG("A test message: ",3.14f);
    YTRACE("A test message: ",3.14f);
}