#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {


// Indicates the primary listing market for the issue.
struct SecurityClass {

    static constexpr auto name = "Security Class";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityClass()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityClass(const char &value)
     : value{ value } {}

    // get value of SecurityClass field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
