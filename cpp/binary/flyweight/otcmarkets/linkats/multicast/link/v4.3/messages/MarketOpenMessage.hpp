#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// This message is sent out at 6 AM on all channels. The message can also be sent mid-day if a
// technical outage caused a temporary closure of the market.
class MarketOpenMessage {
  public:
    static constexpr const char* name = "MarketOpenMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketOpenMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketOpenMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint32_t channel_seq_num() const { return wire::read_u32_be(at(0)); }

    std::chrono::milliseconds market_open() const { return std::chrono::milliseconds(static_cast<std::int64_t>(wire::read_u64_be(at(4)))); }

    std::uint64_t market_close() const { return wire::read_u64_be(at(12)); }

    void print(std::ostream& out) const {
        out << "MarketOpenMessage{";
        out << "channel_seq_num=";
        out << channel_seq_num();
        out << ", market_open=";
        out << market_open().count();
        out << ", market_close=";
        out << market_close();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketOpenMessage& value) {
    value.print(out);
    return out;
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
