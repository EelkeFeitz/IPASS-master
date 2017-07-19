//
//            Copyright (c) 2017, Eelke Feitz
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//        http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"

class HX711 {
private:
    hwlib::target::pin_in & data_pin;
    hwlib::target::pin_out & clock_pin;
    int gain = 27;
public:
    /// \brief HX711 constructor
    /// Initialises the requiered pins for reading data.
    HX711( hwlib::target::pin_in & data_pin, hwlib::target::pin_out & clock_pin ):
        data_pin( data_pin ),
        clock_pin( clock_pin )
    {};
    
    /// \brief get
    /// Waits for the data to be ready, then pulses
    /// the clock pin depening on the gain
    int get() {
        int value = 0x00;
        clock_pin.set( 0 );
        while( data_pin.get() == 1 ) {}
        for( int i = 0; i < gain; i++ ) {
            clock_pin.set( 1 );
            value = value << 0x01;
            hwlib::wait_us( 1 );
            if( data_pin.get() == 1 ){
                value++;
            }
            clock_pin.set( 0 );
            hwlib::wait_us( 1 );
        }
        return value;
    }
};

#endif // HX711_HPP