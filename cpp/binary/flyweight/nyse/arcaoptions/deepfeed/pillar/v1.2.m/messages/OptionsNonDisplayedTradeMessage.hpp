#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/PrintableFlag.hpp"
#include "../enums/NonDisplayedTradeTradeCond1.hpp"
#include "../enums/PriceType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Published as a result of a match between two non-displayed orders.
class OptionsNonDisplayedTradeMessage {
  public:
    static constexpr const char* name = "OptionsNonDisplayedTradeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsNonDisplayedTradeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsNonDisplayedTradeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t trade_id() const { return wire::read_u32_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(16)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(20)); }

    PrintableFlag printable_flag() const { return static_cast<PrintableFlag>(wire::read_u8(at(24))); }

    NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1() const { return static_cast<NonDisplayedTradeTradeCond1>(wire::read_char(at(25))); }

    std::span<const std::byte, 3> reserved_3() const { return bytes_.subspan(26).template first<3>(); }

    PriceType price_type() const { return static_cast<PriceType>(wire::read_u8(at(29))); }

    void print(std::ostream& out) const {
        out << "OptionsNonDisplayedTradeMessage{";
        out << "source_time_ns=";
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
        out << ", printable_flag=";
        out << printable_flag();
        out << ", non_displayed_trade_trade_cond_1=";
        out << non_displayed_trade_trade_cond_1();
        out << ", reserved_3=";
        print::hex(out, reserved_3().data(), reserved_3().size());
        out << ", price_type=";
        out << price_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsNonDisplayedTradeMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
