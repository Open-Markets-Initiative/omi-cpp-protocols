#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class LegalMarket : std::uint8_t {
    NotALegalMarket = 0, // Not A Legal Market
    LegalMarket = 1,     // Legal Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegalMarket value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegalMarket value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
