//
//            Copyright (c) 2017, Eelke Feitz
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//        http://www.boost.org/LICENSE_1_0.txt)
//

#include "load_cell.hpp"

load_cell::load_cell( HX711 & ADconverter ):
    ADconverter( ADconverter )
{}

void load_cell::set_tare() {
    int sum = 0;
    for( int i = 0; i < 5; i++ ){
        sum += ADconverter.get();
    }
    tare = ( sum / 5 );
}

uint_least32_t load_cell::get_tare(){ return tare; }

uint_least32_t load_cell::get_raw() { return ADconverter.get(); }

uint_least32_t load_cell::get_diff() {
    uint_least32_t value = ADconverter.get();
    if( value < tare ) { return 0; }
    return value - tare;
}

uint_least32_t load_cell::get_weight_grams() {
    uint_least32_t value = ADconverter.get();
    if( value < tare) { return 0; }
    return (value - tare) / steps_per_gram;
}

void load_cell::calibrate_grams( int calibrate_weight ) {
    steps_per_gram = ( ADconverter.get() - tare ) / calibrate_weight;
}