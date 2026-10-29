#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SecurityStatus.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/FastMarketIndicator.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Provides state information for a single instrument.
class InstrumentStateChangeMessage {
  public:
    static constexpr const char* name = "InstrumentStateChangeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentStateChangeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentStateChangeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::int64_t security_id() const { return wire::read_i64_le(at(0)); }

    SecurityStatus security_status() const { return static_cast<SecurityStatus>(wire::read_u8(at(8))); }

    SecurityTradingStatus security_trading_status() const { return static_cast<SecurityTradingStatus>(wire::read_u8(at(9))); }

    FastMarketIndicator fast_market_indicator() const { return static_cast<FastMarketIndicator>(wire::read_u8(at(10))); }

    std::span<const std::byte, 5> pad_5() const { return bytes_.subspan(11).template first<5>(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(16)))); }

    void print(std::ostream& out) const {
        out << "InstrumentStateChangeMessage{";
        out << "security_id=";
        out << security_id();
        out << ", security_status=";
        out << security_status();
        out << ", security_trading_status=";
        out << security_trading_status();
        out << ", fast_market_indicator=";
        out << fast_market_indicator();
        out << ", pad_5=";
        print::hex(out, pad_5().data(), pad_5().size());
        out << ", transact_time=";
        out << transact_time().count();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentStateChangeMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
