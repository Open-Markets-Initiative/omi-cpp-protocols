// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a: types/Time.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// Format : HHMMSSmmm (mmm = milliseconds)
struct Time {

    static constexpr const char* name = "Time";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr Time()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit Time(const std::uint32_t value)
     : value{ value } {}

    // get value of Time field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
