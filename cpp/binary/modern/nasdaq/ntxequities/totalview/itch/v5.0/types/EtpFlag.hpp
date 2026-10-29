#pragma once

#include <cstddef>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {


// Indicates whether the security is an exchange traded product (ETP).
struct EtpFlag {

    static constexpr auto name = "Etp Flag";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EtpFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EtpFlag(const char &value)
     : value{ value } {}

    // get value of EtpFlag field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
