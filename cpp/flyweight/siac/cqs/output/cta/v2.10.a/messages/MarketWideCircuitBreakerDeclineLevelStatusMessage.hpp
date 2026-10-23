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

namespace siac::cqs::output::cta::v2_10_a {

// Reports the calculated Level 1, Level 2 and Level 3 threshold values for the current trading
// day necessary to trigger a circuit breaker
class MarketWideCircuitBreakerDeclineLevelStatusMessage {
  public:
    static constexpr const char* name = "MarketWideCircuitBreakerDeclineLevelStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketWideCircuitBreakerDeclineLevelStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketWideCircuitBreakerDeclineLevelStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 47;
    static constexpr std::size_t fixed_size = 47;
    std::size_t encoded_size() const { return 47; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::int64_t mwcb_level_1() const { return wire::read_i64_be(at(22)); }

    std::int64_t mwcb_level_2() const { return wire::read_i64_be(at(30)); }

    std::int64_t mwcb_level_3() const { return wire::read_i64_be(at(38)); }

    char reserved() const { return wire::read_char(at(46)); }

    void print(std::ostream& out) const {
        out << "MarketWideCircuitBreakerDeclineLevelStatusMessage{";
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
        out << ", mwcb_level_1=";
        out << mwcb_level_1();
        out << ", mwcb_level_2=";
        out << mwcb_level_2();
        out << ", mwcb_level_3=";
        out << mwcb_level_3();
        out << ", reserved=";
        print::character(out, reserved());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketWideCircuitBreakerDeclineLevelStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
