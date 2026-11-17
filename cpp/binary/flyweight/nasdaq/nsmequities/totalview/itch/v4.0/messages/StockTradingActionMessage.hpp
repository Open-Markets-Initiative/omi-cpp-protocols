// Nasdaq.NsmEquities.TotalView.Itch.v4.0: messages/StockTradingActionMessage.hpp
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
#include "../enums/TradingState.hpp"
#include "../enums/Reason.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// NASDAQ uses this administrative message to indicate the current trading status of a security
// to the trading community.
class StockTradingActionMessage {
  public:
    static constexpr const char* name = "StockTradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockTradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockTradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::string_view stock() const { return view::text(at(4), 6, ' '); }

    TradingState trading_state() const { return static_cast<TradingState>(wire::read_char(at(10))); }

    std::span<const std::byte, 1> reserved() const { return bytes_.subspan(11).template first<1>(); }

    std::string_view reason() const { return view::text(at(12), 4, ' '); }

    void print(std::ostream& out) const {
        out << "StockTradingActionMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", trading_state=";
        out << trading_state();
        out << ", reserved=";
        print::hex(out, reserved().data(), reserved().size());
        out << ", reason=";
        print::text(out, reason());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StockTradingActionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
