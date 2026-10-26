#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Message type
enum class EquityAndIndexLastSaleMessageType : char {
    Canc = 'A', // Canc
    Oseq = 'B', // Oseq
    Cncl = 'C', // Cncl
    Late = 'D', // Late
    Cnco = 'E', // Cnco
    Open = 'F', // Open
    Cnol = 'G', // Cnol
    Opnl = 'H', // Opnl
    Auto = 'I', // Auto
    Reop = 'J', // Reop
    Ajst = 'K', // Ajst
    Sprd = 'L', // Sprd
    Stdl = 'M', // Stdl
    Stpd = 'N', // Stpd
    Cstp = 'O', // Cstp
    Bwrt = 'P', // Bwrt
    Cmbo = 'Q', // Cmbo
    Spim = 'R', // Spim
    Isoi = 'S', // Isoi
    Bnmt = 'T', // Bnmt
    Xmpt = 'X', // Xmpt
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EquityAndIndexLastSaleMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EquityAndIndexLastSaleMessageType value);

} // namespace siac::opra::output::obi::v6_2
