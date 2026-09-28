#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates whether the security is an exchange traded product
enum class EtpFlag : char {
    Etp = 'Y',          // Etp
    NotEtp = 'N',       // Not Etp
    NotAvailable = ' ', // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EtpFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EtpFlag value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
