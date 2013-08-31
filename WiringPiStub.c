//Wiring pi stub

#define INPUT 0
#define PUD_UP 0
#define INT_EDGE_BOTH 0

static int _count = 0;

inline int digitalRead(int pin)
{
    return _count++;
}

inline void pinMode(int pin, int par)
{

}

inline void pullUpDnControl(int pin, int par)
{

}

inline void wiringPiISR(int pin, int par, void (*f)(void))
{

}
