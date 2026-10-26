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
#include "../enums/MarketCode.hpp"
#include "../enums/OperationalHaltAction.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// The Exchange uses this message to indicate the current Operational Status of a security to
// the trading community.
class OperationalHaltMessage {
  public:
    static constexpr const char* name = "OperationalHaltMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OperationalHaltMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OperationalHaltMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 18;
    static constexpr std::size_t fixed_size = 18;
    std::size_t encoded_size() const { return 18; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp().count())); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    MarketCode market_code() const { return static_cast<MarketCode>(wire::read_char(at(16))); }

    OperationalHaltAction operational_halt_action() const { return static_cast<OperationalHaltAction>(wire::read_char(at(17))); }

    void print(std::ostream& out) const {
        out << "OperationalHaltMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        calendar::print(out, time_stamp().count(), 1, "America/New_York");
        out << ", stock=";
        print::text(out, stock());
        out << ", market_code=";
        out << market_code();
        out << ", operational_halt_action=";
        out << operational_halt_action();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OperationalHaltMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
