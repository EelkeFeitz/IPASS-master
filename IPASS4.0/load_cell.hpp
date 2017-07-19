//
//            Copyright (c) 2017, Eelke Feitz
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//        http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef LOAD_CELL_HPP
#define LOAD_CELL_HPP

#include "HX711.hpp"

class load_cell {
private:
    uint_least32_t tare;
    uint_least32_t steps_per_gram;
    HX711 & ADconverter;
public:
    /// \brief load_cell constructor
    /// initializez ADconverter object.
    load_cell( HX711 & ADconverter );
    
    /// \brief set_tare
    /// Makes tare the avarage of 5 readings.
    void set_tare();
    
    /// \brief get_tare
    /// Returns tare.
    uint_least32_t get_tare();

    /// \brief get_raw
    /// Returns the uncut digital input from the HX711 chip.
    uint_least32_t get_raw();
    
    /// \brief get_diff()
    /// Returns 0 if the current reading is lower than tare.
    /// Returns the difference between the current reading
    /// and tare.
    uint_least32_t get_diff();
    
    /// \brief get_weight_grams
    /// Returns 0 if the current reading is lower than tare.
    /// Returns the amouts of grams on the scale.
    uint_least32_t get_weight_grams();
    
    /// \brief calibrate_grams
    /// Takes 'calibrate_weight'.
    /// Sets 'steps_per_gram' as the diference of the current reading and tare
    /// devided by the given 'calibrate_weight'.
    void calibrate_grams( int calibrate_weight );
};

#endif // LOAD_CELL_HPP