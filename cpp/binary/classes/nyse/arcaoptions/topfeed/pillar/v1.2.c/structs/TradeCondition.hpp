#pragma once

#include <array>
#include <cstddef>
#include <ostream>

#include "../enums/Opening.hpp"
#include "../enums/Series.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Trade Condition
class TradeCondition {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    TradeCondition() = default;
    TradeCondition(Series series, Opening opening, const std::array<std::byte, 1>& reserved_1, char offical);

    // Series: Settlement related conditions. Valid values:
    Series series() const;
    void set_series(Series value);

    // Opening: Reserved for future use
    Opening opening() const;
    void set_opening(Opening value);

    // Reserved 1: This field is reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Offical: Reserved for future use
    char offical() const;
    void set_offical(char value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TradeCondition& other) const;
    bool operator!=(const TradeCondition& other) const;

  private:
    Series series_{};
    Opening opening_{};
    std::array<std::byte, 1> reserved_1_{};
    char offical_{};
};

std::ostream& operator<<(std::ostream& out, const TradeCondition& value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
