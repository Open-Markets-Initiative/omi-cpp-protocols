#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/SecurityTradingStatusReason.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// SecurityTradingStatusMessage
class SecurityTradingStatusMessage {
  public:
    static constexpr const char* name = "SecurityTradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityTradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityTradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t security_id() const { return wire::read_u16_be(at(8)); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_char(at(10))); }

    SecurityTradingStatusReason security_trading_status_reason() const { return static_cast<SecurityTradingStatusReason>(wire::read_char(at(11))); }

    void print(std::ostream& out) const {
        out << "SecurityTradingStatusMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", security_id=";
        out << security_id();
        out << ", security_trading_status=";
        out << security_trading_status();
        out << ", security_trading_status_reason=";
        out << security_trading_status_reason();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityTradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
