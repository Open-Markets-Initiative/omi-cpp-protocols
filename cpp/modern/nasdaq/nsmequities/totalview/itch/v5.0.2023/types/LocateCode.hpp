#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Locate code identifying the security
struct LocateCode {

    static constexpr const char* name = "Locate Code";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr LocateCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LocateCode(const std::uint16_t value)
     : value{ std::byteswap(value) } {}

    // get value of LocateCode field
    [[nodiscard]] std::uint16_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint16_t value;
};
}
