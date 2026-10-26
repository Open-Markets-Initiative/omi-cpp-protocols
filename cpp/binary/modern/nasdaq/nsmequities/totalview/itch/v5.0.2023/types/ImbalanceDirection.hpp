#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// The market side of the order imbalance
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
