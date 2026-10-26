#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/IndexValueDenominatorCode.hpp"
#include "../common/Decimal.hpp"

namespace siac::opra::output::obi::v6_2 {

// Underlying Value last sale Message
class UnderlyingValueLastSaleMessage {
  public:
    static constexpr const char* name = "UnderlyingValueLastSaleMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingValueLastSaleMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingValueLastSaleMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    char message_indicator() const { return wire::read_char(at(0)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::string_view security_symbol() const { return view::text(at(9), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(14).template first<1>(); }

    IndexValueDenominatorCode index_value_denominator_code() const { return static_cast<IndexValueDenominatorCode>(wire::read_char(at(15))); }

    // the exponent index_value_denominator_code states, or 0 for a code it does not state
    static constexpr int index_value_exponent(char code) {
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
    Decimal index_value() const { return Decimal(static_cast<std::int64_t>(wire::read_i32_be(at(16))), index_value_exponent(static_cast<char>(index_value_denominator_code()))); }

    std::span<const std::byte, 4> reserved_4() const { return bytes_.subspan(20).template first<4>(); }

    void print(std::ostream& out) const {
        out << "UnderlyingValueLastSaleMessage{";
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
        out << ", index_value_denominator_code=";
        out << index_value_denominator_code();
        out << ", index_value=";
        out << index_value();
        out << ", reserved_4=";
        print::hex(out, reserved_4().data(), reserved_4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingValueLastSaleMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
