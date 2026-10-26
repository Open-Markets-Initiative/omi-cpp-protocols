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
#include "../enums/SourceVenue.hpp"
#include "../enums/TradingStatus.hpp"
#include "../enums/SessionChangeReason.hpp"
#include "../enums/OrderBookType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Used to communicate scheduled and unscheduled session changes. When sent in the recovery
// channel, used to indicate the current trading status of an instrument.
class InstrumentStatusMessage {
  public:
    static constexpr const char* name = "InstrumentStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 27;
    static constexpr std::size_t fixed_size = 27;
    std::size_t encoded_size() const { return 27; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(8)); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(16))); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(18))); }

    SessionChangeReason session_change_reason() const { return static_cast<SessionChangeReason>(wire::read_u8(at(19))); }

    std::string_view new_end_time() const { return view::text(at(20), 6, ' '); }

    OrderBookType order_book_type() const { return static_cast<OrderBookType>(wire::read_u8(at(26))); }

    void print(std::ostream& out) const {
        out << "InstrumentStatusMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument=";
        out << instrument();
        out << ", source_venue=";
        out << source_venue();
        out << ", trading_status=";
        out << trading_status();
        out << ", session_change_reason=";
        out << session_change_reason();
        out << ", new_end_time=";
        print::text(out, new_end_time());
        out << ", order_book_type=";
        out << order_book_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
