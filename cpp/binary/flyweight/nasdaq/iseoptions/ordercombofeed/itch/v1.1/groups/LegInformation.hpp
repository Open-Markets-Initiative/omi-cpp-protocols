#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"
#include "../enums/OptionType.hpp"
#include "../enums/LegSide.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Leg information
class LegInformation {
  public:
    static constexpr const char* name = "LegInformation";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LegInformation(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LegInformation has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::uint32_t option_id() const { return wire::read_u32_be(at(0)); }

    std::string_view security_symbol() const { return view::text(at(4), 6, ' '); }

    std::uint8_t leg_id() const { return wire::read_u8(at(10)); }

    std::uint8_t expiration_year() const { return wire::read_u8(at(11)); }

    std::uint8_t expiration_month() const { return wire::read_u8(at(12)); }

    std::uint8_t expiration_day() const { return wire::read_u8(at(13)); }

    Decimal explicit_strike_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(14))), -8); }

    OptionType option_type() const { return static_cast<OptionType>(wire::read_char(at(22))); }

    LegSide leg_side() const { return static_cast<LegSide>(wire::read_char(at(23))); }

    std::uint32_t leg_ratio() const { return wire::read_u32_be(at(24)); }

    void print(std::ostream& out) const {
        out << "LegInformation{";
        out << "option_id=";
        out << option_id();
        out << ", security_symbol=";
        print::text(out, security_symbol());
        out << ", leg_id=";
        out << static_cast<int>(leg_id());
        out << ", expiration_year=";
        out << static_cast<int>(expiration_year());
        out << ", expiration_month=";
        out << static_cast<int>(expiration_month());
        out << ", expiration_day=";
        out << static_cast<int>(expiration_day());
        out << ", explicit_strike_price=";
        out << explicit_strike_price();
        out << ", option_type=";
        out << option_type();
        out << ", leg_side=";
        out << leg_side();
        out << ", leg_ratio=";
        out << leg_ratio();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LegInformation& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
