#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradeCond1.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The Refresh Complex Trade message is sent in the event no Complex Trade messages are
// published for the symbol for 2 consecutive minutes.
class RefreshComplexTradeMessage {
  public:
    static constexpr const char* name = "RefreshComplexTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RefreshComplexTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RefreshComplexTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t complex_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(16)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t volume_4() const { return wire::read_u32_le(at(24)); }

    TradeCond1 trade_cond_1() const { return static_cast<TradeCond1>(wire::read_char(at(28))); }

    char trade_cond_2() const { return wire::read_char(at(29)); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(30).template first<2>(); }

    void print(std::ostream& out) const {
        out << "RefreshComplexTradeMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", complex_index=";
        out << complex_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", trade_id=";
        out << trade_id();
        out << ", price=";
        out << price();
        out << ", volume_4=";
        out << volume_4();
        out << ", trade_cond_1=";
        out << trade_cond_1();
        out << ", trade_cond_2=";
        print::character(out, trade_cond_2());
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RefreshComplexTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
