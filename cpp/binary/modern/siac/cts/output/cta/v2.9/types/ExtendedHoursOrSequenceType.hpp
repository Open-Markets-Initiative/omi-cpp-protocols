#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Category 3: Extended Hours Or Sequence Type
struct ExtendedHoursOrSequenceType {

    static constexpr auto name = "Extended Hours Or Sequence Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExtendedHoursOrSequenceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExtendedHoursOrSequenceType(const char &value)
     : value{ value } {}

    // get value of ExtendedHoursOrSequenceType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
