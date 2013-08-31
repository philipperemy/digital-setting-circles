#include "Encoder.h"

std::vector<Encoder*> Encoder::_encoders_ptr;

Encoder::Encoder(int pin_a, int pin_b)
: pin_a(pin_a), pin_b(pin_b)
{
    setup_encoder();
}

Encoder::~Encoder()
{
    //dtor
}

void Encoder::update_encoder()
{
    int MSB = digitalRead(pin_a);
    int LSB = digitalRead(pin_b);

    int encoded = (MSB << 1) | LSB;
    int sum = (last_encoded << 2) | encoded;

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    {
        value++;
    }

    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    {
        value--;
    }

    last_encoded = encoded;
}

void Encoder::register_to_callback()
{
    call_back_encoder_ptr = &encoderNameSpace::_callback;
    _encoders_ptr.push_back(this);
}

void Encoder::setup_encoder()
{
    register_to_callback();

    value = 0;
    last_encoded = 0;

    pinMode(pin_a, INPUT);
    pinMode(pin_b, INPUT);
    pullUpDnControl(pin_a, PUD_UP);
    pullUpDnControl(pin_b, PUD_UP);
    wiringPiISR(pin_a, INT_EDGE_BOTH, call_back_encoder_ptr);
    wiringPiISR(pin_b, INT_EDGE_BOTH, call_back_encoder_ptr);

}

long Encoder::get_value()
{
    return value;
}
