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

namespace siac::opra::output::obi::v6_2 {

// Equity and Index Last Sale Message
class EquityAndIndexLastSaleMessage {
  public:
    static constexpr const char* name = "EquityAndIndexLastSaleMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EquityAndIndexLastSaleMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EquityAndIndexLastSaleMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

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

    PremiumPriceDenominatorCode premium_price_denominator_code() const { return static_cast<PremiumPriceDenominatorCode>(wire::read_char(at(27))); }

    // the exponent premium_price_denominator_code states, or 0 for a code it does not state
    static constexpr int premium_price_exponent(char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'F': return -6;
            case 'G': return -7;
            case 'I': return 0;
            default: return 0;
        }
    }
    Decimal premium_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(28))), premium_price_exponent(static_cast<char>(premium_price_denominator_code()))); }

    std::uint32_t trade_identifier() const { return wire::read_u32_be(at(32)); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(36).template first<4>(); }

    void print(std::ostream& out) const {
        out << "EquityAndIndexLastSaleMessage{";
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
        out << ", premium_price_denominator_code=";
        out << premium_price_denominator_code();
        out << ", premium_price=";
        out << premium_price();
        out << ", trade_identifier=";
        out << trade_identifier();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EquityAndIndexLastSaleMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
