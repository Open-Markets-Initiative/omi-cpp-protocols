#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../enums/RpiIndicator.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

// A quote message is sent when any event results in a new top of book value on either side of
// the market.
class QuoteMessage {
  public:
    static constexpr const char* name = "QuoteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit QuoteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every QuoteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t ask_price() const { return wire::read_u32_le(at(12)); }

    std::uint32_t ask_volume() const { return wire::read_u32_le(at(16)); }

    std::uint32_t bid_price() const { return wire::read_u32_le(at(20)); }

    std::uint32_t bid_volume() const { return wire::read_u32_le(at(24)); }

    QuoteCondition quote_condition() const { return static_cast<QuoteCondition>(wire::read_char(at(28))); }

    RpiIndicator rpi_indicator() const { return static_cast<RpiIndicator>(wire::read_char(at(29))); }

    void print(std::ostream& out) const {
        out << "QuoteMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
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
        out << ", rpi_indicator=";
        out << rpi_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const QuoteMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
