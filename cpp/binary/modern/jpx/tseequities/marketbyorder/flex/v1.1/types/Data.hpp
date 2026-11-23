// Jpx.TseEquities.MarketByOrder.Flex.v1.1: types/Data.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Variable length payload of FLEX tags including their packet headers
struct Data {

    static constexpr auto name = "Data";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Data()
     : value{} {}

  protected:
    type value;
};
}
