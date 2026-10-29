#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Scope value
struct Scope {

    static constexpr auto name = "Scope";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Scope()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Scope(const char &value)
     : value{ value } {}

    // get value of Scope field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
