#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Auction Response information
class AuctionResponse {
  public:
    static constexpr const char* name = "AuctionResponse";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionResponse(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionResponse has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    Decimal response_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(0))), -4); }

    std::uint32_t response_size() const { return wire::read_u32_be(at(4)); }

    void print(std::ostream& out) const {
        out << "AuctionResponse{";
        out << "response_price=";
        out << response_price();
        out << ", response_size=";
        out << response_size();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionResponse& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
