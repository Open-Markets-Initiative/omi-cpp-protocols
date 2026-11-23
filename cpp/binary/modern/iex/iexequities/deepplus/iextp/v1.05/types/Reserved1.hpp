// Iex.IexEquities.DeepPlus.IexTp.v1.05: types/Reserved1.hpp
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::iextp::v1_05 {


// Reserved for future use
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Reserved1()
     : value{} {}

  protected:
    type value;
};
}
