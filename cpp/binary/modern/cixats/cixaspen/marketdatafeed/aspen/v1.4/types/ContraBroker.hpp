#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Three digit number Broker Number of the contra order or 001 for anonymous
struct ContraBroker {

    static constexpr auto name = "Contra Broker";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ContraBroker()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContraBroker(const type &value)
     : value{ value } {}

    // get value of ContraBroker field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
