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

// TRF Fractional Trade Message. New message effective 1/12/26.
class TrfFractionalTradeMessage {
  public:
    static constexpr const char* name = "TrfFractionalTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TrfFractionalTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TrfFractionalTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint64_t fractional_volume() const { return wire::read_u64_le(at(24)); }

    TradeCond1 trade_cond_1() const { return static_cast<TradeCond1>(wire::read_char(at(32))); }

    TradeCond2 trade_cond_2() const { return static_cast<TradeCond2>(wire::read_char(at(33))); }

    TradeCond3 trade_cond_3() const { return static_cast<TradeCond3>(wire::read_char(at(34))); }

    TradeCond4 trade_cond_4() const { return static_cast<TradeCond4>(wire::read_char(at(35))); }

    std::uint32_t exec_day_time() const { return wire::read_u32_le(at(36)); }

    std::uint32_t exec_day_time_ns() const { return wire::read_u32_le(at(40)); }

    void print(std::ostream& out) const {
        out << "TrfFractionalTradeMessage{";
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
        out << ", fractional_volume=";
        out << fractional_volume();
        out << ", trade_cond_1=";
        out << trade_cond_1();
        out << ", trade_cond_2=";
        out << trade_cond_2();
        out << ", trade_cond_3=";
        out << trade_cond_3();
        out << ", trade_cond_4=";
        out << trade_cond_4();
        out << ", exec_day_time=";
        out << exec_day_time();
        out << ", exec_day_time_ns=";
        out << exec_day_time_ns();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TrfFractionalTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
