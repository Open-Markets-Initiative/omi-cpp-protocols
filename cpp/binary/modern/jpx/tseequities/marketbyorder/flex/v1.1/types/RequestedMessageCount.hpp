#pragma once

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// For retransmission set to the number of messages from the first sequence number; for snapshot set to 0
struct RequestedMessageCount {

    static constexpr const char* name = "Requested Message Count";
    static constexpr std::size_t size =  3;

    // 3 wire bytes, read into the type that holds them
    using type = std::uint32_t;

    // default constructor
    constexpr RequestedMessageCount()
     : value{} {}

    // standard constructor
    constexpr explicit RequestedMessageCount(const std::uint32_t number)
     : value{ bytes(number) } {}

    // get value of RequestedMessageCount field
    [[nodiscard]] std::uint32_t get() const {
        std::uint32_t result = 0;
        for (std::size_t index = 0; index < size; ++index) {
            result = static_cast<std::uint32_t>((result << 8) | value[index]);
        }

        return result;
    }

  protected:
    // the value's bytes, as the wire holds them
    static constexpr std::array<std::uint8_t, size> bytes(const std::uint32_t number) {
        std::array<std::uint8_t, size> result{};
        for (std::size_t index = size; index > 0; --index) {
            result[index - 1] = static_cast<std::uint8_t>(number >> (((size - index)) * 8));
        }

        return result;
    }

    std::array<std::uint8_t, size> value;
};
}
