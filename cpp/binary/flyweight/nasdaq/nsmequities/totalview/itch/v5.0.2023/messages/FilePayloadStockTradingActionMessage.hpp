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
#include "../enums/TradingState.hpp"
#include "../enums/ReasonCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Nasdaq uses this administrative message to indicate the current trading status of a security
// to the trading community
class FilePayloadStockTradingActionMessage {
  public:
    static constexpr const char* name = "FilePayloadStockTradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit FilePayloadStockTradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every FilePayloadStockTradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    TradingState trading_state() const { return static_cast<TradingState>(wire::read_char(at(18))); }

    char reserved() const { return wire::read_char(at(19)); }

    std::string_view reason_code() const { return view::text(at(20), 4, ' '); }

    void print(std::ostream& out) const {
        out << "FilePayloadStockTradingActionMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
        out << ", stock=";
        print::text(out, stock());
        out << ", trading_state=";
        out << trading_state();
        out << ", reserved=";
        print::character(out, reserved());
        out << ", reason_code=";
        print::text(out, reason_code());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const FilePayloadStockTradingActionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
