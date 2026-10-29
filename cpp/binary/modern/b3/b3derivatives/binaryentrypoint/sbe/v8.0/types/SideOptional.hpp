#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// side
struct SideOptional {

    static constexpr auto name = "Side Optional";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr SideOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SideOptional(const char &value)
     : value{ value } {}

    // get value of SideOptional field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
