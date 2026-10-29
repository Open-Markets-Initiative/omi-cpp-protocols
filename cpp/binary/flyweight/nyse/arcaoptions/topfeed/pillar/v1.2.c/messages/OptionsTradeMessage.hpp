#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/TradeCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// An Options Trade message is sent when there is an execution on the order book.
class OptionsTradeMessage {
  public:
    static constexpr const char* name = "OptionsTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    TradeCondition trade_condition() const { return TradeCondition{ bytes_.subspan(28) }; }

    void print(std::ostream& out) const {
        out << "OptionsTradeMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", trade_condition=";
        trade_condition().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
