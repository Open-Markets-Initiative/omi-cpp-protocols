#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Number of auction Responses. Next two fields repeat that number of times. Allowable values for this field are 0 or 1.
struct NumberOfResponses {

    static constexpr auto name = "Number Of Responses";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumberOfResponses()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfResponses(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumberOfResponses field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
