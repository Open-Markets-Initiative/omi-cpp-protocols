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

namespace siac::opra::output::obi::v6_2 {

// Underlying value bid and offer message
class UnderlyingValueBidAndOfferMessage {
  public:
    static constexpr const char* name = "UnderlyingValueBidAndOfferMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingValueBidAndOfferMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingValueBidAndOfferMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    char message_indicator() const { return wire::read_char(at(0)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(1)); }

    std::uint32_t participant_reference_number() const { return wire::read_u32_be(at(5)); }

    std::string_view security_symbol() const { return view::text(at(9), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(14).template first<1>(); }

    IndexValueDenominatorCode index_value_denominator_code() const { return static_cast<IndexValueDenominatorCode>(wire::read_char(at(15))); }

    std::int32_t bid_index_value() const { return wire::read_i32_be(at(16)); }

    std::int64_t offer_index_value() const { return wire::read_i64_be(at(20)); }

    void print(std::ostream& out) const {
        out << "UnderlyingValueBidAndOfferMessage{";
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
        out << ", bid_index_value=";
        out << bid_index_value();
        out << ", offer_index_value=";
        out << offer_index_value();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingValueBidAndOfferMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
