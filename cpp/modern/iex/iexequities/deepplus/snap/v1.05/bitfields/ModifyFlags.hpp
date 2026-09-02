#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Modify Flags
struct ModifyFlags {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Modify Flags";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Priority = 0x80;
    };

    // default constructor
    constexpr ModifyFlags()
     : value{ 0 } {}

    // Order Priority
    [[nodiscard]] constexpr bool Priority() const {
        return value & mask::Priority;
    }

  protected:
    type value;
};
}
