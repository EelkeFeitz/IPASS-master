//
//            Copyright (c) 2017, Eelke Feitz
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//        http://www.boost.org/LICENSE_1_0.txt)
//

/// \mainpage HX711 library
/// \section Introduction
/// This library is written by Eelke.J.J.Feitz as part of the final assesment for his propedeuse year.

#include "hwlib.hpp"
#include "HX711.hpp"
#include "load_cell.hpp"
#include "tongling_rly.hpp"

/// \brief main
/// Initializes the requiered pins.
/// sets up an bit-banged i2c interface.
/// Keeps checking for the presence of a cup on the scale.
/// If there is, closes solenoid valves so air pressure can build up in the tanks.
/// The scale reads the maximum weight value, or the cup is preampively removed.
/// Then  opens the solenoid valves, Releasing the build up air pressure in the bottles.
/// Starts over again.
int main( void ) {
//    kill the watchdog
     WDT->WDT_MR = WDT_MR_WDDIS;
    
//    buttons setup
    auto button_A = hwlib::target::pin_in ( hwlib::target::pins::d0 );
    
//    oled setup
    auto scl     = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda     = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c );  
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::window_ostream( oled, font );
    
//    HX711 setup
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d7 );
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d6 );
    auto c_hx711 = HX711(DT, SCK);
    
//    load_cell setup
    uint_least32_t calibreer_gewicht = 244;
    uint_least32_t consumptie_gewicht = 200;
    auto weegschaal = load_cell( c_hx711 );
    
//    relay setup
    auto relay_valve_pin = hwlib::target::pin_out( hwlib::target::pins::d8 );
    auto relay_valve = tongling_rly( relay_valve_pin );
    
    oled.clear();
    display << "\f" << "setting tare" << hwlib::flush;
    hwlib::wait_ms( 1000 );
    weegschaal.set_tare();
    oled.clear();
    display << "\f" << "Place empty glass" << hwlib::flush;
    hwlib::wait_ms( 2500 );
    weegschaal.calibrate_grams( calibreer_gewicht );
    oled.clear();

    while( true ) {
        oled.clear();
        display << "\f" 
                << "raw : " << weegschaal.get_raw() << '\n'
                << "tare: " << weegschaal.get_tare() << '\n' 
                << "diff: " << weegschaal.get_diff() << '\n'
                << "gram: " << weegschaal.get_weight_grams() << '\n'
                << "glas: " << "absent" << '\n'
                << "inst: " << "PLACE GLASS" << '\n'
                << hwlib::flush;
        hwlib::wait_ms( 1000 );
        
        while( ( weegschaal.get_weight_grams() >= calibreer_gewicht - 10 ) && ( weegschaal.get_weight_grams() < ( calibreer_gewicht + consumptie_gewicht ) ) ) {
            oled.clear();
            display << "\f" 
                    << "raw : " << weegschaal.get_raw() << '\n'
                    << "tare: " << weegschaal.get_tare() << '\n' 
                    << "diff: " << weegschaal.get_raw() - weegschaal.get_tare() << '\n'
                    << "gram: " << weegschaal.get_weight_grams() << '\n'
                    << "glas: " << "present" << '\n'
                    << "inst: " << "SLCT DRINK" << '\n'
                    << hwlib::flush;
            relay_valve.set_power_to_NC();
            hwlib::wait_ms( 1000 );
        }
        relay_valve.set_power_to_NO();
        
        while( weegschaal.get_weight_grams() != 0 ) {
            oled.clear();
            display << "\f" 
                    << "raw : " << weegschaal.get_raw() << '\n'
                    << "tare: " << weegschaal.get_tare() << '\n' 
                    << "diff: " << weegschaal.get_diff() << '\n'
                    << "gram: " << weegschaal.get_weight_grams() << '\n'
                    << "glas: " << "present" << '\n'
                    << "inst: " << "TAKE GLASS" << '\n'
                    << hwlib::flush;
            hwlib::wait_ms( 1000 );
        }
        if( !button_A.get() ) { weegschaal.set_tare(); }
    }
}