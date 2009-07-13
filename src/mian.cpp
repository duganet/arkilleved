//main.cpp
#include "Frame.h"
int main(int argc, char**argv)
{
    Frame frame;
    if(frame.main_loop() == false)
    {
        return 1;
    }
    return 0;
}
