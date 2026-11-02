#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// A price level consolidated from multiple venues
class ConsolidatedBidAskPair {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    ConsolidatedBidAskPair() = default;
    ConsolidatedBidAskPair(std::optional<Decimal> bid_px, std::optional<Decimal> ask_px, std::uint32_t bid_sz, std::uint32_t ask_sz, std::uint16_t bid_pb, const std::array<std::byte, 2>& reserved_2, std::uint16_t ask_pb, const std::array<std::byte, 2>& second_reserved_2);

    // Bid Px: The bid price
    std::optional<Decimal> bid_px() const;
    void set_bid_px(std::optional<Decimal> value);

    // Ask Px: The ask price
    std::optional<Decimal> ask_px() const;
    void set_ask_px(std::optional<Decimal> value);

    // Bid Sz: The bid size
    std::uint32_t bid_sz() const;
    void set_bid_sz(std::uint32_t value);

    // Ask Sz: The ask size
    std::uint32_t ask_sz() const;
    void set_ask_sz(std::uint32_t value);

    // Bid Pb: The publisher ID indicating the venue containing the best bid
    std::uint16_t bid_pb() const;
    void set_bid_pb(std::uint16_t value);

    // Reserved 2: Reserved, 2 bytes
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Ask Pb: The publisher ID indicating the venue containing the best ask
    std::uint16_t ask_pb() const;
    void set_ask_pb(std::uint16_t value);

    // Second Reserved 2: Reserved, 2 bytes
    const std::array<std::byte, 2>& second_reserved_2() const;
    std::array<std::byte, 2>& second_reserved_2();
    void set_second_reserved_2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ConsolidatedBidAskPair& other) const;
    bool operator!=(const ConsolidatedBidAskPair& other) const;

  private:
    std::optional<Decimal> bid_px_{};
    std::optional<Decimal> ask_px_{};
    std::uint32_t bid_sz_{};
    std::uint32_t ask_sz_{};
    std::uint16_t bid_pb_{};
    std::array<std::byte, 2> reserved_2_{};
    std::uint16_t ask_pb_{};
    std::array<std::byte, 2> second_reserved_2_{};
};

std::ostream& operator<<(std::ostream& out, const ConsolidatedBidAskPair& value);

} // namespace databento::marketdata::normalized::dbn::v1
