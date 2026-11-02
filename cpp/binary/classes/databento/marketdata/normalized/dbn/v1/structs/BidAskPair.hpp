#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// A level
class BidAskPair {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    BidAskPair() = default;
    BidAskPair(std::optional<Decimal> bid_px, std::optional<Decimal> ask_px, std::uint32_t bid_sz, std::uint32_t ask_sz, std::uint32_t bid_ct, std::uint32_t ask_ct);

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

    // Bid Ct: The number of bid orders
    std::uint32_t bid_ct() const;
    void set_bid_ct(std::uint32_t value);

    // Ask Ct: The number of ask orders
    std::uint32_t ask_ct() const;
    void set_ask_ct(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BidAskPair& other) const;
    bool operator!=(const BidAskPair& other) const;

  private:
    std::optional<Decimal> bid_px_{};
    std::optional<Decimal> ask_px_{};
    std::uint32_t bid_sz_{};
    std::uint32_t ask_sz_{};
    std::uint32_t bid_ct_{};
    std::uint32_t ask_ct_{};
};

std::ostream& operator<<(std::ostream& out, const BidAskPair& value);

} // namespace databento::marketdata::normalized::dbn::v1
