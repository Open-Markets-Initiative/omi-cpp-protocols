#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// The Nasdaq cross session for which the message is being generated
struct CrossType {

    static constexpr auto name = "Cross Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CrossType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossType(const char &value)
     : value{ value } {}

    // get value of CrossType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
