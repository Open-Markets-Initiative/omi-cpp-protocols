#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Denotes the MWCB Level that was breached
struct BreachedLevel {

    static constexpr auto name = "Breached Level";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr BreachedLevel()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BreachedLevel(const char &value)
     : value{ value } {}

    // get value of BreachedLevel field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
