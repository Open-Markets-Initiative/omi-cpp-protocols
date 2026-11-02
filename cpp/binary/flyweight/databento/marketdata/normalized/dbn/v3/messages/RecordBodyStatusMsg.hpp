#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/StatusAction.hpp"
#include "../enums/StatusReason.hpp"
#include "../enums/TradingEvent.hpp"
#include "../enums/IsTrading.hpp"
#include "../enums/IsQuoting.hpp"
#include "../enums/IsShortSellRestricted.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// A trading status update message; the record of the status schema
class RecordBodyStatusMsg {
  public:
    static constexpr const char* name = "RecordBodyStatusMsg";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordBodyStatusMsg(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordBodyStatusMsg has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::optional<std::chrono::nanoseconds> ts_recv() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    StatusAction status_action() const { return static_cast<StatusAction>(wire::read_u16_le(at(8))); }

    StatusReason status_reason() const { return static_cast<StatusReason>(wire::read_u16_le(at(10))); }

    TradingEvent trading_event() const { return static_cast<TradingEvent>(wire::read_u16_le(at(12))); }

    IsTrading is_trading() const { return static_cast<IsTrading>(wire::read_char(at(14))); }

    IsQuoting is_quoting() const { return static_cast<IsQuoting>(wire::read_char(at(15))); }

    IsShortSellRestricted is_short_sell_restricted() const { return static_cast<IsShortSellRestricted>(wire::read_char(at(16))); }

    std::span<const std::byte, 7> reserved_7() const { return bytes_.subspan(17).template first<7>(); }

    void print(std::ostream& out) const {
        out << "RecordBodyStatusMsg{";
        out << "ts_recv=";
        print::optional_duration(out, ts_recv());
        out << ", status_action=";
        out << status_action();
        out << ", status_reason=";
        out << status_reason();
        out << ", trading_event=";
        out << trading_event();
        out << ", is_trading=";
        out << is_trading();
        out << ", is_quoting=";
        out << is_quoting();
        out << ", is_short_sell_restricted=";
        out << is_short_sell_restricted();
        out << ", reserved_7=";
        print::hex(out, reserved_7().data(), reserved_7().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordBodyStatusMsg& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v3
