#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::snap::v1_6 {

// Channel identifier from the Deep feed IexTp header
struct ChannelId {

    static constexpr const char* name = "Channel Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ChannelId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ChannelId(const std::uint32_t value)
     : value{ value } {}

    // get value of ChannelId field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
