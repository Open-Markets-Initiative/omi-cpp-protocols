#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

class Visitor;

// The Snapshot Request message is sent from the client to the Deep Snap server to authenticate
// and request a Snapshot Response
class SnapshotRequestMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SnapshotRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 56;

    SnapshotRequestMessage() = default;
    SnapshotRequestMessage(const std::string& authentication_token, std::uint32_t channel_id, std::uint32_t session_id, std::uint64_t minimum_sequence_number);

    // Authentication Token: Token supplied by Iex Market Ops, left justified and space padded
    // on the right
    const std::string& authentication_token() const;
    std::string& authentication_token();
    void set_authentication_token(const std::string& value);

    // Channel Id: Channel identifier from the Deep feed IexTp header
    std::uint32_t channel_id() const;
    void set_channel_id(std::uint32_t value);

    // Session Id: Session identifier from the Deep feed IexTp header
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Minimum Sequence Number: Minimum sequence number useable by the client, zero returns the
    // latest snapshot available
    std::uint64_t minimum_sequence_number() const;
    void set_minimum_sequence_number(std::uint64_t value);

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

    bool operator==(const SnapshotRequestMessage& other) const;
    bool operator!=(const SnapshotRequestMessage& other) const;

  private:
    std::string authentication_token_{};
    std::uint32_t channel_id_{};
    std::uint32_t session_id_{};
    std::uint64_t minimum_sequence_number_{};
};

} // namespace iex::iexequities::deep::snap::v1_6
