#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// This message is sent whenever a Side order is executed in whole or in part. It is possible
// to receive several Single Side Executed Messages for the same Side order if that Side order
// is executed in several parts. The multiple Single Side Executed Messages on the same order
// are cumulative. By combining the executions received separately via two types of Single Side
// Executed Messages and Trade Messages, it is possible to build a complete view of all
// non-auction executions that happen on NASDAQ. Auction execution information is available in
// one bulk print via the Auction Trade Message.
class SingleSideExecutedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::SingleSideExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 28;

    SingleSideExecutedMessage() = default;
    SingleSideExecutedMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t reference_number, std::uint32_t executed_contracts, std::uint32_t cross_number, std::uint32_t match_number);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Reference Number: The order/quote reference number associated with the executed order.
    std::uint64_t reference_number() const;
    void set_reference_number(std::uint64_t value);

    // Executed Contracts: The number of contracts executed.
    std::uint32_t executed_contracts() const;
    void set_executed_contracts(std::uint32_t value);

    // Cross Number: Trade Group Id. Ties together all trades of a given atomic transaction in
    // the matching engine.
    std::uint32_t cross_number() const;
    void set_cross_number(std::uint32_t value);

    // Match Number: Execution Id. Identifies the component of an execution. Unique for a given
    // day. The match number is also referenced in the Trade Break Message.
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const SingleSideExecutedMessage& other) const;
    bool operator!=(const SingleSideExecutedMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t reference_number_{};
    std::uint32_t executed_contracts_{};
    std::uint32_t cross_number_{};
    std::uint32_t match_number_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
