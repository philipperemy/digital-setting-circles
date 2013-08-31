#define MAX_ENCODERS 2
#include <vector>
#include <ostream>
#include <iostream>

#include "WiringPiStub.c"

#ifndef ENCODER_H
#define ENCODER_H


class Encoder
{
public:
    Encoder(int pin_a, int pin_b);
    ~Encoder();
    void update_encoder();
    long get_value();
    const int pin_a;
    const int pin_b;

    static std::vector<Encoder*> _encoders_ptr;

protected:
private:
    void setup_encoder();
    void register_to_callback();
    volatile long value;
    volatile int last_encoded;
    void (*call_back_encoder_ptr)(void);
};

const std::vector<Encoder*> _encoders_ptr;

namespace encoderNameSpace
{
    inline void _callback(void)
    {
        for(int i = 0; i < (int) Encoder::_encoders_ptr.size(); i++)
        {
            Encoder::_encoders_ptr[i]->update_encoder();
        }
    }
}

#endif // ENCODER_H
