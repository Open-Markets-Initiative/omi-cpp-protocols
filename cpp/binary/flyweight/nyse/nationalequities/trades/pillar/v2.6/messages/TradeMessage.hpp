#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradeCond1.hpp"
#include "../enums/TradeCond2.hpp"
#include "../enums/TradeCond3.hpp"
#include "../enums/TradeCond4.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

// A Trade message is sent when there is an execution on the order book.
class TradeMessage {
  public:
    static constexpr const char* name = "TradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    TradeCond1 trade_cond_1() const { return static_cast<TradeCond1>(wire::read_char(at(28))); }

    TradeCond2 trade_cond_2() const { return static_cast<TradeCond2>(wire::read_char(at(29))); }

    TradeCond3 trade_cond_3() const { return static_cast<TradeCond3>(wire::read_char(at(30))); }

    TradeCond4 trade_cond_4() const { return static_cast<TradeCond4>(wire::read_char(at(31))); }

    void print(std::ostream& out) const {
        out << "TradeMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", trade_cond_1=";
        out << trade_cond_1();
        out << ", trade_cond_2=";
        out << trade_cond_2();
        out << ", trade_cond_3=";
        out << trade_cond_3();
        out << ", trade_cond_4=";
        out << trade_cond_4();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
