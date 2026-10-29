#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CrossType.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// A Cross Trade message is published on completion of a crossing auction.
class CrossTradeMessage {
  public:
    static constexpr const char* name = "CrossTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t cross_id() const { return wire::read_u32_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(16)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(20)); }

    CrossType cross_type() const { return static_cast<CrossType>(wire::read_char(at(24))); }

    void print(std::ostream& out) const {
        out << "CrossTradeMessage{";
        out << "source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", cross_id=";
        out << cross_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", cross_type=";
        out << cross_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
