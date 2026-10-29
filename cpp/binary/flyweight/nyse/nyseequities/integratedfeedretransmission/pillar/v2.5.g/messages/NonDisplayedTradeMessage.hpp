#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PrintableFlag.hpp"
#include "../enums/TradeCond1.hpp"
#include "../enums/TradeCond2.hpp"
#include "../enums/TradeCond3.hpp"
#include "../enums/TradeCond4.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// A Non Displayed Trade message is sent as a result of a match between two non-displayed
// orders.
class NonDisplayedTradeMessage {
  public:
    static constexpr const char* name = "NonDisplayedTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NonDisplayedTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NonDisplayedTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(16)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(20)); }

    PrintableFlag printable_flag() const { return static_cast<PrintableFlag>(wire::read_u8(at(24))); }

    TradeCond1 trade_cond_1() const { return static_cast<TradeCond1>(wire::read_char(at(25))); }

    TradeCond2 trade_cond_2() const { return static_cast<TradeCond2>(wire::read_char(at(26))); }

    TradeCond3 trade_cond_3() const { return static_cast<TradeCond3>(wire::read_char(at(27))); }

    TradeCond4 trade_cond_4() const { return static_cast<TradeCond4>(wire::read_char(at(28))); }

    void print(std::ostream& out) const {
        out << "NonDisplayedTradeMessage{";
        out << "source_time_ns=";
        out << source_time_ns().count();
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
        out << ", printable_flag=";
        out << printable_flag();
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

inline std::ostream& operator<<(std::ostream& out, const NonDisplayedTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
