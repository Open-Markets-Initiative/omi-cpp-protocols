#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteCondition.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// The Complex Quote message is a two-sided message providing best bid and offer limits of
// orders on complex symbols with aggregated volumes at each limit.
class ComplexQuoteMessage {
  public:
    static constexpr const char* name = "ComplexQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t complex_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(12)); }

    std::int32_t ask_price() const { return wire::read_i32_le(at(16)); }

    std::int32_t bid_price() const { return wire::read_i32_le(at(20)); }

    std::uint16_t ask_volume() const { return wire::read_u16_le(at(24)); }

    std::uint16_t bid_volume() const { return wire::read_u16_le(at(26)); }

    std::uint16_t ask_customer_volume() const { return wire::read_u16_le(at(28)); }

    std::uint16_t bid_customer_volume() const { return wire::read_u16_le(at(30)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(32))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(33).template first<1>(); }

    std::span<const std::byte, 2> reserved_2() const { return bytes_.subspan(34).template first<2>(); }

    void print(std::ostream& out) const {
        out << "ComplexQuoteMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", complex_index=";
        out << complex_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", ask_price=";
        out << ask_price();
        out << ", bid_price=";
        out << bid_price();
        out << ", ask_volume=";
        out << ask_volume();
        out << ", bid_volume=";
        out << bid_volume();
        out << ", ask_customer_volume=";
        out << ask_customer_volume();
        out << ", bid_customer_volume=";
        out << bid_customer_volume();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", reserved_2=";
        print::hex(out, reserved_2().data(), reserved_2().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
