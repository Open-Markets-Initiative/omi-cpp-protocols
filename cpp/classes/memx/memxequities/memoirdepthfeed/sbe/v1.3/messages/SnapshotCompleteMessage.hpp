#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// SnapshotCompleteMessage
class SnapshotCompleteMessage : public Payload {
  public:
    // The code that selects this message
    static constexpr PayloadCode message_type = TemplateId::SnapshotCompleteMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    SnapshotCompleteMessage() = default;
    SnapshotCompleteMessage(std::chrono::nanoseconds timestamp, std::uint64_t as_of_sequence_number);

    // Timestamp: Timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // As Of Sequence Number: AsOfSequenceNumber
    std::uint64_t as_of_sequence_number() const;
    void set_as_of_sequence_number(std::uint64_t value);

    // Payload
    PayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PayloadVisitor& visitor) const override;
    std::unique_ptr<Payload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Payload& other) const override;

    bool operator==(const SnapshotCompleteMessage& other) const;
    bool operator!=(const SnapshotCompleteMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t as_of_sequence_number_{};
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
