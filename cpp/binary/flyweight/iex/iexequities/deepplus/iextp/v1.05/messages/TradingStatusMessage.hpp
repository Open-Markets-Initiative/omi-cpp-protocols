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
#include "../enums/TradingStatus.hpp"

namespace iex::iexequities::deepplus::iextp::v1_05 {

// The Trading Status Message is used to indicate the current trading status of a security.
class TradingStatusMessage {
  public:
    static constexpr const char* name = "TradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::string_view reason() const { return view::text(at(17), 4, ' '); }

    void print(std::ostream& out) const {
        out << "TradingStatusMessage{";
        out << "trading_status=";
        out << trading_status();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", reason=";
        print::text(out, reason());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deepplus::iextp::v1_05
