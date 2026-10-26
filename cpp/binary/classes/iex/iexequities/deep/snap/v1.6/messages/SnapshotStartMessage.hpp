#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

class Visitor;

// First message of a Snapshot Response sent from the Deep Snap server when a Snapshot Request
// is successful
class SnapshotStartMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SnapshotStartMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 8;

    SnapshotStartMessage() = default;
    SnapshotStartMessage(std::uint64_t snapshot_length);

    // Snapshot Length: Length in bytes of the complete Snapshot Response including the
    // Snapshot Start message, all Snapshot Data messages, and the Snapshot End message
    std::uint64_t snapshot_length() const;
    void set_snapshot_length(std::uint64_t value);

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

    bool operator==(const SnapshotStartMessage& other) const;
    bool operator!=(const SnapshotStartMessage& other) const;

  private:
    std::uint64_t snapshot_length_{};
};

} // namespace iex::iexequities::deep::snap::v1_6
