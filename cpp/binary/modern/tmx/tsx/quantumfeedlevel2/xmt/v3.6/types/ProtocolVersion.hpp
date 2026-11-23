// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/ProtocolVersion.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// Protocol major version number
struct ProtocolVersion {

    static constexpr auto name = "Protocol Version";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ProtocolVersion()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProtocolVersion(const char &value)
     : value{ value } {}

    // get value of ProtocolVersion field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
