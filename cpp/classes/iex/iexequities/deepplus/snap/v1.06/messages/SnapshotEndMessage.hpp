#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

class Visitor;

// Final message of a Snapshot Response, carries the sequence number at which the snapshot was
// created
class SnapshotEndMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SnapshotEndMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    SnapshotEndMessage() = default;
    SnapshotEndMessage(std::uint64_t snapshot_sequence_number);

    // Snapshot Sequence Number: Sequence at which the snapshot was created
    std::uint64_t snapshot_sequence_number() const;
    void set_snapshot_sequence_number(std::uint64_t value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const SnapshotEndMessage& other) const;
    bool operator!=(const SnapshotEndMessage& other) const;

  private:
    std::uint64_t snapshot_sequence_number_{};
};

} // namespace iex::iexequities::deepplus::snap::v1_06
