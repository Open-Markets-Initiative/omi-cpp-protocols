#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// For listed equity markets, the market where this symbol is listed.
enum class ExchangeCode : char {
    NyseAmerican = 'A',                      // Nyse American
    Txse = 'F',                              // Txse
    Ltse = 'L',                              // Ltse
    NyseTexas = 'M',                         // Nyse Texas
    Nyse = 'N',                              // Nyse
    NyseArca = 'P',                          // Nyse Arca
    Nasdaq = 'Q',                            // Nasdaq
    Iex = 'V',                               // Iex
    Cboe = 'Z',                              // Cboe
    OtcOrIndexBasedProductSpaceOr0X20 = ' ', // Otc Or Index Based Product Space Or 0 X 20
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExchangeCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExchangeCode value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
