#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/StrategyType.hpp"
#include "../groups/LegInformation.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Whenever a complex order is added in the system for an underlying, the order is normalized
// and results in either the creation of a new complex strategy or is added to an existing
// strategy. A Complex Strategy Message containing the strategy definition will be sent.
class ComplexStrategyDirectoryMessage {
  public:
    static constexpr const char* name = "ComplexStrategyDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ComplexStrategyDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ComplexStrategyDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 26;
    std::size_t encoded_size() const { return leg_information_end(); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    StrategyType strategy_type() const { return static_cast<StrategyType>(wire::read_char(at(10))); }

    std::uint8_t source() const { return wire::read_u8(at(11)); }

    std::string_view underlying_symbol() const { return view::text(at(12), 13, ' '); }

    std::uint8_t number_of_legs() const { return wire::read_u8(at(25)); }

    view::entries<LegInformation> leg_information() const { return view::entries<LegInformation>{ bytes_.subspan(26), wire::count(number_of_legs()) }; }

    void print(std::ostream& out) const {
        out << "ComplexStrategyDirectoryMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", strategy_type=";
        out << strategy_type();
        out << ", source=";
        out << static_cast<int>(source());
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", number_of_legs=";
        out << static_cast<int>(number_of_legs());
        out << ", leg_information=";
        print::sequence(out, leg_information());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t leg_information_end() const { return 26 + leg_information().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ComplexStrategyDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
