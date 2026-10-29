#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken.
class BrokenTradeMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'B';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    BrokenTradeMessage() = default;
    BrokenTradeMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t match_number);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Match Number: The NASDAQ generated day-unique Match Number of this execution. The match
    // number is also referenced in the Trade Break Message.
    std::uint64_t match_number() const;
    void set_match_number(std::uint64_t value);

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

    bool operator==(const BrokenTradeMessage& other) const;
    bool operator!=(const BrokenTradeMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint64_t match_number_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
