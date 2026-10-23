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
#include "../enums/SecurityClass.hpp"
#include "../enums/CurrentTradingState.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Nasdaq uses this administrative message to indicate the current trading status of a security
// to the trading community.
class StockTradingActionMessage {
  public:
    static constexpr const char* name = "StockTradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockTradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockTradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 22;
    static constexpr std::size_t fixed_size = 22;
    std::size_t encoded_size() const { return 22; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(16))); }

    CurrentTradingState current_trading_state() const { return static_cast<CurrentTradingState>(wire::read_char(at(17))); }

    std::string_view reason() const { return view::text(at(18), 4, ' '); }

    void print(std::ostream& out) const {
        out << "StockTradingActionMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        out << time_stamp().count();
        out << ", stock=";
        print::text(out, stock());
        out << ", security_class=";
        out << security_class();
        out << ", current_trading_state=";
        out << current_trading_state();
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

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
