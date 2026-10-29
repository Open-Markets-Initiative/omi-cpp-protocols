#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// Timestamp of when the instrument was last added, modified or deleted
struct LastUpdateTime {

    static constexpr auto name = "Last Update Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;

    // default constructor
    constexpr LastUpdateTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastUpdateTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of LastUpdateTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
