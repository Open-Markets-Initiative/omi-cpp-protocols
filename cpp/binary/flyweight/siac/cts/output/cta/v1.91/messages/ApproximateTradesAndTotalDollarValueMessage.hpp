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
#include "../common/Decimal.hpp"

namespace siac::cts::output::cta::v1_91 {

// The Approximate Trades and Total Dollar Value message allows a Participant to report the
// total trades and total dollar value of trades at their respective market centers.
class ApproximateTradesAndTotalDollarValueMessage {
  public:
    static constexpr const char* name = "ApproximateTradesAndTotalDollarValueMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ApproximateTradesAndTotalDollarValueMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ApproximateTradesAndTotalDollarValueMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 34;
    static constexpr std::size_t fixed_size = 34;
    std::size_t encoded_size() const { return 34; }

    ParticipantId participant_id() const { return static_cast<ParticipantId>(wire::read_char(at(0))); }

    Timestamp1 timestamp_1() const { return Timestamp1{ bytes_.subspan(1) }; }

    std::uint8_t message_id() const { return wire::read_u8(at(9)); }

    std::uint32_t transaction_id() const { return wire::read_u32_be(at(10)); }

    std::int64_t participant_reference_number() const { return wire::read_i64_be(at(14)); }

    std::uint32_t total_trades() const { return wire::read_u32_be(at(22)); }

    Decimal dollar_value() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(26))), -6); }

    void print(std::ostream& out) const {
        out << "ApproximateTradesAndTotalDollarValueMessage{";
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
        out << ", total_trades=";
        out << total_trades();
        out << ", dollar_value=";
        out << dollar_value();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ApproximateTradesAndTotalDollarValueMessage& value) {
    value.print(out);
    return out;
}

} // namespace siac::cts::output::cta::v1_91
