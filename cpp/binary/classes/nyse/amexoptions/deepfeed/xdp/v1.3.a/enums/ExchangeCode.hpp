#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Exchanges where it is listed
enum class ExchangeCode : char {
    Nyse = 'N',                   // Nyse
    NyseArca = 'P',               // Nyse Arca
    Nasdaq = 'Q',                 // Nasdaq
    NyseMkt = 'A',                // Nyse Mkt
    GlobalOtc = '1',              // Global Otc
    ArcaLocalNonTapeBIndex = '2', // Arca Local Non Tape B Index
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExchangeCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExchangeCode value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
