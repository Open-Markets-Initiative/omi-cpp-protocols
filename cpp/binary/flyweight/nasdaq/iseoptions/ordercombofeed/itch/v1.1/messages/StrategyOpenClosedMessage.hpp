#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/OpenState.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// The options system uses this administrative message to indicate when an strategy has
// completed the opening process and is now available for auto execution or when the option has
// closed and is no longer available for auto execution.
class StrategyOpenClosedMessage {
  public:
    static constexpr const char* name = "StrategyOpenClosedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StrategyOpenClosedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StrategyOpenClosedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(0)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t strategy_id() const { return wire::read_u32_be(at(6)); }

    OpenState open_state() const { return static_cast<OpenState>(wire::read_char(at(10))); }

    void print(std::ostream& out) const {
        out << "StrategyOpenClosedMessage{";
        out << "timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", strategy_id=";
        out << strategy_id();
        out << ", open_state=";
        out << open_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StrategyOpenClosedMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
