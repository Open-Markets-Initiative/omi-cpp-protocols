#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {


// orderCategory
struct OrderCategory {

    static constexpr auto name = "Order Category";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr OrderCategory()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderCategory(const char &value)
     : value{ value } {}

    // get value of OrderCategory field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
