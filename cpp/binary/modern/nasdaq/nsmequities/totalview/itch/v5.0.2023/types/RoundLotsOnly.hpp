#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates if Nasdaq system limits order entry for issue
struct RoundLotsOnly {

    static constexpr auto name = "Round Lots Only";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RoundLotsOnly()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RoundLotsOnly(const char &value)
     : value{ value } {}

    // get value of RoundLotsOnly field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
