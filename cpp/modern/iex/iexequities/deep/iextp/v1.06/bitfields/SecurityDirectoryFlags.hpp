#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_06 {

// Security Directory Flags
struct SecurityDirectoryFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Security Directory Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Etp = 0x20;
        static const type WhenIssued = 0x40;
        static const type TestSecurity = 0x80;
    };

    // default constructor
    constexpr SecurityDirectoryFlags()
     : value{ 0 } {}

    // Symbol is an ETP
    [[nodiscard]] constexpr bool Etp() const {
        return value & mask::Etp;
    }

    // Symbol is a when issued security
    [[nodiscard]] constexpr bool WhenIssued() const {
        return value & mask::WhenIssued;
    }

    // Symbol is a test security
    [[nodiscard]] constexpr bool TestSecurity() const {
        return value & mask::TestSecurity;
    }

  protected:
    type value;
};
}
