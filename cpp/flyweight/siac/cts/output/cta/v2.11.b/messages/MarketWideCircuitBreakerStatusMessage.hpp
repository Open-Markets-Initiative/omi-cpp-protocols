#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../enums/MarketWideCircuitBreakerLevelIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Reports the Market-Wide Circuit Breaker threshold Level that has been breached
class MarketWideCircuitBreakerStatusMessage {
  public:
    static constexpr const char* name = "MarketWideCircuitBreakerStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketWideCircuitBreakerStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketWideCircuitBreakerStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    MarketWideCircuitBreakerLevelIndicator market_wide_circuit_breaker_level_indicator() const { return static_cast<MarketWideCircuitBreakerLevelIndicator>(wire::read_char(at(22))); }

    char reserved() const { return wire::read_char(at(23)); }

    void print(std::ostream& out) const {
        out << "MarketWideCircuitBreakerStatusMessage{";
        out << "participant_id=";
        out << participant_id();
        out << ", timestamp_1=";
        timestamp_1().print(out);
        out << ", message_id=";
        out << static_cast<int>(message_id());
        out << ", transaction_id=";
        out << transaction_id();
        out << ", participant_reference_number=";
        out << participant_reference_number();
        out << ", market_wide_circuit_breaker_level_indicator=";
        out << market_wide_circuit_breaker_level_indicator();
        out << ", reserved=";
        print::character(out, reserved());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketWideCircuitBreakerStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v2_11_b
