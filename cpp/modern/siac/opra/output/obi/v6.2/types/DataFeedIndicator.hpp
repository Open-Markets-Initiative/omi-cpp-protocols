#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Value is ‘O’ for OPRA
struct DataFeedIndicator {

    static constexpr auto name = "Data Feed Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr DataFeedIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DataFeedIndicator(const char &value)
     : value{ value } {}

    // get value of DataFeedIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
