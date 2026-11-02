#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The publisher ID assigned by Databento, which denotes the dataset and venue
struct PublisherId {

    static constexpr const char* name = "Publisher Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PublisherId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PublisherId(const std::uint16_t value)
     : value{ value } {}

    // get value of PublisherId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
