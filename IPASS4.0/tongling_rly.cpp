/**
 * \file
 * \brief    main.cpp
 * \author    Eelke Feitz
 * \copyright  Copyright (c) 2017, Eelke Feitz
 *
 * \page License
 *
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

#include "tongling_rly.hpp"

tongling_rly::tongling_rly( hwlib::target::pin_out & rly_pin ):
    rly_pin( rly_pin )
{}

void tongling_rly::set_power_to_NC() {
    rly_pin.set( 1 );
}

void tongling_rly::set_power_to_NO() {
    rly_pin.set( 0 );
}

//          Copyright Eelke Feitz 2016 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)