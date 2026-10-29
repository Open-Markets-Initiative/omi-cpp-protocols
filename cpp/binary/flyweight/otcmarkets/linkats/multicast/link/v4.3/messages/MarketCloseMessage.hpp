#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message is sent out at 5 PM on all channels. The message can also be sent mid-day if a
// technical outage causes a temporary closure of the market.
class MarketCloseMessage {
  public:
    static constexpr const char* name = "MarketCloseMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketCloseMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketCloseMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::uint64_t market_close_time_milli() const { return wire::read_u64_be(at(4)); }

    std::uint32_t market_msg_ct() const { return wire::read_u32_be(at(12)); }

    void print(std::ostream& out) const {
        out << "MarketCloseMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", market_close_time_milli=";
        out << market_close_time_milli();
        out << ", market_msg_ct=";
        out << market_msg_ct();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketCloseMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
