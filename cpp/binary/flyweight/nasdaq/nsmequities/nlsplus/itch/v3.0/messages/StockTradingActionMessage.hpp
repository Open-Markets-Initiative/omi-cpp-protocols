#pragma once

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

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates the current trading status of a security to the trading community. Clients should
// initialize all securities as halted at the start of the session.
class StockTradingActionMessage {
  public:
    static constexpr const char* name = "StockTradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockTradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockTradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 15;
    static constexpr std::size_t fixed_size = 15;
    std::size_t encoded_size() const { return 15; }

    char reserved() const { return wire::read_char(at(0)); }

    std::string_view issue_symbol() const { return view::text(at(1), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(9))); }

    CurrentTradingState current_trading_state() const { return static_cast<CurrentTradingState>(wire::read_char(at(10))); }

    std::string_view reason() const { return view::text(at(11), 4, ' '); }

    void print(std::ostream& out) const {
        out << "StockTradingActionMessage{";
        out << "reserved=";
        print::character(out, reserved());
        out << ", issue_symbol=";
        print::text(out, issue_symbol());
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

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
