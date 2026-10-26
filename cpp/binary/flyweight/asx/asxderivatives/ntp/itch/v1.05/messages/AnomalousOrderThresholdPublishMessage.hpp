#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message disseminates price band information to the market advising the setting, zeroing
// or adjusting of the Extreme Trade Range price, the Anomalous Order Threshold price and the
// associated ranges for a contract that requires Market Integrity Rules enforcement
class AnomalousOrderThresholdPublishMessage {
  public:
    static constexpr const char* name = "AnomalousOrderThresholdPublishMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AnomalousOrderThresholdPublishMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AnomalousOrderThresholdPublishMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 58;
    static constexpr std::size_t fixed_size = 58;
    std::size_t encoded_size() const { return 58; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    Decimal aot_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(10))), -2); }

    Decimal aot_upper_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(18))), -2); }

    Decimal aot_lower_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(26))), -2); }

    Decimal etr_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(34))), -2); }

    Decimal etr_upper_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(42))), -2); }

    Decimal etr_lower_price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(50))), -2); }

    void print(std::ostream& out) const {
        out << "AnomalousOrderThresholdPublishMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", aot_price=";
        out << aot_price();
        out << ", aot_upper_price=";
        out << aot_upper_price();
        out << ", aot_lower_price=";
        out << aot_lower_price();
        out << ", etr_price=";
        out << etr_price();
        out << ", etr_upper_price=";
        out << etr_upper_price();
        out << ", etr_lower_price=";
        out << etr_lower_price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AnomalousOrderThresholdPublishMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
