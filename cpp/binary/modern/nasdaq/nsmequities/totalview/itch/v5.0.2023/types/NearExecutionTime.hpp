// Nasdaq.NsmEquities.TotalView.Itch.v5.0.2023: types/NearExecutionTime.hpp
#pragma once

#include <bit>
#include <chrono>
#include <cstddef>
#include <cstdint>

#include "../common/Day.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The time at which the Near Execution Price was determined
struct NearExecutionTime {

    static constexpr const char* name = "Near Execution Time";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr NearExecutionTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NearExecutionTime(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of NearExecutionTime field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

    // NearExecutionTime on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    [[nodiscard]] std::int64_t utc(const calendar::Day& day) const {
        return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(get()));
    }

  protected:
    std::uint64_t value;
};
}
