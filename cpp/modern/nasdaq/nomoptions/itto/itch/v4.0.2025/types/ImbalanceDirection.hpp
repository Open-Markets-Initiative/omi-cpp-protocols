#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// Indicates the market side of the imbalance
struct ImbalanceDirection {

    static constexpr auto name = "Imbalance Direction";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ImbalanceDirection()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceDirection(const char &value)
     : value{ value } {}

    // get value of ImbalanceDirection field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
