#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class SecurityExchange : char {
    Cboe = 'C',                   // Cboe
    OneChicagoNotSupported = 'O', // One Chicago Not Supported
    CbsxNotSupported = 'W',       // Cbsx Not Supported
    Cfecof = 'F',                 // Cfecof
    Cboe2Options = '2',           // Cboe 2 Options
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityExchange value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityExchange value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
