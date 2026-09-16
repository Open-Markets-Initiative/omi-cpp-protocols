#pragma once

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Order quantity registered on the order book in number of shares
struct Quantity {

    static constexpr auto name = "Quantity";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<std::uint8_t, size>;

    // default constructor
    constexpr Quantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Quantity(const std::uint64_t value)
     : value{ bytes(value) } {}

    // get value of Quantity field
    [[nodiscard]] std::uint64_t get() const {
        std::uint64_t result = 0;
        for (std::size_t index = 0; index < size; ++index) {
            result = (result << 8) + value[index];
        }

        return result;
    }

    // UTC epoch nanoseconds: this nanoseconds-since-midnight value placed on
    // the capture's trading day. The day's midnight is recovered from the
    // capture time by removing this time-of-day and snapping to the whole
    // hour (every exchange midnight falls on a whole UTC hour), so it stays
    // correct across daylight-saving changes without a fixed timezone offset.
    [[nodiscard]] std::int64_t utc(const std::int64_t capture_ns) const {
        constexpr std::int64_t hour = 3600000000000LL;
        const std::int64_t since_midnight = static_cast<std::int64_t>(get());
        const std::int64_t approximate = capture_ns - since_midnight;
        const std::int64_t midnight = ((approximate + hour / 2) / hour) * hour;
        return midnight + since_midnight;
    }

  protected:
    // the low six bytes of a value, most significant first, as the wire holds them
    static constexpr type bytes(const std::uint64_t value) {
        type result{};
        for (std::size_t index = 0; index < size; ++index) {
            result[size - 1 - index] = static_cast<std::uint8_t>(value >> (8 * index));
        }

        return result;
    }

    type value;
};
}
