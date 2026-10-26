#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/ExpirationBlock.hpp"
#include "../enums/StrikePriceDenominatorCode.hpp"
#include "../common/Decimal.hpp"
#include "../enums/PremiumPriceDenominatorCode.hpp"
#include "../enums/UnderlyingPriceDenominatorCode.hpp"

namespace siac::opra::output::obi::v6_2 {

// Equity and Index End of Day Summary Message
class EquityAndIndexEndOfDaySummaryMessage {
  public:
    static constexpr const char* name = "EquityAndIndexEndOfDaySummaryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EquityAndIndexEndOfDaySummaryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EquityAndIndexEndOfDaySummaryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 69;
    static constexpr std::size_t fixed_size = 69;
    std::size_t encoded_size() const { return 69; }

    char message_indicator() const { return wire::read_char(at(0)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::string_view security_symbol() const { return view::text(at(9), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(14).template first<1>(); }

    ExpirationBlock expiration_block() const { return ExpirationBlock{ bytes_.subspan(15) }; }

    StrikePriceDenominatorCode strike_price_denominator_code() const { return static_cast<StrikePriceDenominatorCode>(wire::read_char(at(18))); }

    // the exponent strike_price_denominator_code states, or 0 for a code it does not state
    static constexpr int strike_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(19))), strike_price_exponent(static_cast<char>(strike_price_denominator_code()))); }

    std::uint32_t volume() const { return wire::read_u32_be(at(23)); }

    std::uint32_t open_interest_volume() const { return wire::read_u32_be(at(27)); }

    PremiumPriceDenominatorCode premium_price_denominator_code() const { return static_cast<PremiumPriceDenominatorCode>(wire::read_char(at(31))); }

    std::int32_t open_price() const { return wire::read_i32_be(at(32)); }

    std::int32_t high_price() const { return wire::read_i32_be(at(36)); }

    std::int32_t low_price() const { return wire::read_i32_be(at(40)); }

    std::int32_t last_price() const { return wire::read_i32_be(at(44)); }

    std::int32_t net_change() const { return wire::read_i32_be(at(48)); }

    UnderlyingPriceDenominatorCode underlying_price_denominator_code() const { return static_cast<UnderlyingPriceDenominatorCode>(wire::read_char(at(52))); }

    // the exponent underlying_price_denominator_code states, or 0 for a code it does not state
    static constexpr int underlying_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'F': return -6;
            case 'G': return -7;
            case 'H': return -8;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal underlying_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(53))), underlying_price_exponent(static_cast<char>(underlying_price_denominator_code()))); }

    std::int32_t bid_price() const { return wire::read_i32_be(at(61)); }

    std::int32_t offer_price() const { return wire::read_i32_be(at(65)); }

    void print(std::ostream& out) const {
        out << "EquityAndIndexEndOfDaySummaryMessage{";
        out << "message_indicator=";
        print::character(out, message_indicator());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", expiration_block=";
        expiration_block().print(out);
        out << ", strike_price_denominator_code=";
        out << strike_price_denominator_code();
        out << ", strike_price=";
        out << strike_price();
        out << ", volume=";
        out << volume();
        out << ", open_interest_volume=";
        out << open_interest_volume();
        out << ", premium_price_denominator_code=";
        out << premium_price_denominator_code();
        out << ", open_price=";
        out << open_price();
        out << ", high_price=";
        out << high_price();
        out << ", low_price=";
        out << low_price();
        out << ", last_price=";
        out << last_price();
        out << ", net_change=";
        out << net_change();
        out << ", underlying_price_denominator_code=";
        out << underlying_price_denominator_code();
        out << ", underlying_price=";
        out << underlying_price();
        out << ", bid_price=";
        out << bid_price();
        out << ", offer_price=";
        out << offer_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EquityAndIndexEndOfDaySummaryMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
