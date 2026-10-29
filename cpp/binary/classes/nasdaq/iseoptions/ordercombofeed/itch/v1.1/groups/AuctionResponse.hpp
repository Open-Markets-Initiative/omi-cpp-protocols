#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Auction Response information
class AuctionResponse {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    AuctionResponse() = default;
    AuctionResponse(Decimal response_price, std::uint32_t response_size);

    // Response Price: Price of the auction response in fixed point format with 6 whole number
    // places followed by 4 decimal digits. The response, if shown (zero if not shown) is the
    // best response on the contra side.
    Decimal response_price() const;
    void set_response_price(Decimal value);

    // Response Size: Size of the auction response (zero if not shown).
    std::uint32_t response_size() const;
    void set_response_size(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const AuctionResponse& other) const;
    bool operator!=(const AuctionResponse& other) const;

  private:
    Decimal response_price_{ 0, -4 };
    std::uint32_t response_size_{};
};

std::ostream& operator<<(std::ostream& out, const AuctionResponse& value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
