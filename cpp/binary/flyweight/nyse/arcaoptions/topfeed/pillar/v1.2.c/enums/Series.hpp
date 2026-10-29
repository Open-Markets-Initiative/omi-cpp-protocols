#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Settlement related conditions. Valid values:
enum class Series : char {
    Cube = 'a',                                                   // Cube
    Occ = 'c',                                                    // Occ
    FloorTrade = 'e',                                             // Floor Trade
    OtherOutrightSeries = 'I',                                    // Other Outright Series
    IsoSweep = 'S',                                               // Iso Sweep
    After90Seconds = 'D',                                         // After 90 Seconds
    OtherComplexOrders = 'f',                                     // Other Complex Orders
    ComplexCube = 'g',                                            // Complex Cube
    ComplexQccOrder = 'H',                                        // Complex Qcc Order
    ComplexFloorOrder = 'i',                                      // Complex Floor Order
    ComplexOrderTradingWithTheOutrightSeries = 'j',               // Complex Order Trading With The Outright Series
    ComplexOrderToOutrightSeriesOrderfloorTrade = 'm',            // Complex Order To Outright Series Orderfloor Trade
    ComplexOrderWithStockToComplexOrderWithStockFloorTrade = 'p', // Complex Order With Stock To Complex Order With Stock Floor Trade
    ComplexOrderWithStockToOutrightSeriesOrderFloorTrade = 's',   // Complex Order With Stock To Outright Series Order Floor Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Series value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Series value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
