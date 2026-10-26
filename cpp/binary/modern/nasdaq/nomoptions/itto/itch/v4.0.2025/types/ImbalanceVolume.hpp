#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The imbalance volume.
struct ImbalanceVolume {

    static constexpr const char* name = "Imbalance Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ImbalanceVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ImbalanceVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
