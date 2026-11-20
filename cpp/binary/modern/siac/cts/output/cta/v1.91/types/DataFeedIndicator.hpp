// Siac.Cts.Output.Cta.v1.91: types/DataFeedIndicator.hpp
#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// T for Consolidated Tape System (CTS)
struct DataFeedIndicator {

    static constexpr auto name = "Data Feed Indicator";
    static constexpr std::size_t size = 1;
    using type = char;
static const type static_value = 'T';

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
