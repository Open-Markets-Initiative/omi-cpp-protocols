#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// An Options quote message is sent when any event results in a new top of book value on either
// side of the market
class OptionsQuoteMessage {
  public:
    static constexpr const char* name = "OptionsQuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsQuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsQuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 38;
    static constexpr std::size_t fixed_size = 38;
    std::size_t encoded_size() const { return 38; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::int32_t ask_price() const { return wire::read_i32_le(at(12)); }

    std::uint32_t ask_volume() const { return wire::read_u32_le(at(16)); }

    std::int32_t bid_price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t bid_volume() const { return wire::read_u32_le(at(24)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(28))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(29).template first<1>(); }

    std::uint32_t ask_customer_volume() const { return wire::read_u32_le(at(30)); }

    std::uint32_t bid_customer_volume() const { return wire::read_u32_le(at(34)); }

    void print(std::ostream& out) const {
        out << "OptionsQuoteMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", ask_price=";
        out << ask_price();
        out << ", ask_volume=";
        out << ask_volume();
        out << ", bid_price=";
        out << bid_price();
        out << ", bid_volume=";
        out << bid_volume();
        out << ", quote_condition=";
        out << quote_condition();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", ask_customer_volume=";
        out << ask_customer_volume();
        out << ", bid_customer_volume=";
        out << bid_customer_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsQuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
