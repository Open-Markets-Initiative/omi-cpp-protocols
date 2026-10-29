#pragma once

#include <cstddef>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {


// Denotes if an issue or quoting participant record is set-up in Nasdaq systems in a live/production, test, or demo state.
struct Authenticity {

    static constexpr auto name = "Authenticity";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Authenticity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Authenticity(const char &value)
     : value{ value } {}

    // get value of Authenticity field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
