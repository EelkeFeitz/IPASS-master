//
//            Copyright (c) 2017, Eelke Feitz
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//        http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef TONGLING_RLY_HPP
#define TONGLING_RLY_HPP

#include "hwlib.hpp"

class tongling_rly {
private:
    hwlib::target::pin_out & rly_pin;
public:
    /// \brief relays constructor
    /// Initializes the requiered pin.
    tongling_rly( hwlib::target::pin_out & rly_pin );
    
    /// \brief set_power_to_NC
    /// Sets the power to the cirquit port that without triggering
    /// is Normally Closed.
    void set_power_to_NC();
    
    /// \brief set_power_to_NO
    /// Sets the power to the cirquit port that without triggering
    /// is Normally Open.
    void set_power_to_NO();
};

#endif // TONGLING_RLY_HPP