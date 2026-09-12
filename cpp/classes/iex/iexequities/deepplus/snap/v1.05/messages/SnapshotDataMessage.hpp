#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/IexTpMessageType.hpp"
#include "../messages/IexTpMessageData.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

class Visitor;
class IexTpMessageDataVisitor;

// Carries one complete Deep Plus feed message wrapped with an IexTp header providing Deep Plus
// feed sequencing and timing information
class SnapshotDataMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SnapshotDataMessage;

    SnapshotDataMessage() = default;
    SnapshotDataMessage(const SnapshotDataMessage& other);
    SnapshotDataMessage& operator=(const SnapshotDataMessage& other);
    SnapshotDataMessage(SnapshotDataMessage&& other) noexcept = default;
    SnapshotDataMessage& operator=(SnapshotDataMessage&& other) noexcept = default;
    ~SnapshotDataMessage() = default;

    // Iex Tp Header: IexTp header for the wrapped Deep Plus feed message, see the Iex
    // Transport specification
    char iex_tp_header() const;
    void set_iex_tp_header(char value);

    // Iex Tp Message Block Length: Length of the IexTp message block, see the Iex Transport
    // specification
    std::uint16_t iex_tp_message_block_length() const;
    void set_iex_tp_message_block_length(std::uint16_t value);

    // Iex Tp Message Length: Length of the wrapped Deep Plus message in bytes not including
    // this field
    std::uint16_t iex_tp_message_length() const;
    void set_iex_tp_message_length(std::uint16_t value);

    // Iex Tp Message Type: Code identifying the wrapped Deep Plus message type
    IexTpMessageType iex_tp_message_type() const;
    void set_iex_tp_message_type(IexTpMessageType value);

    // Iex Tp Message Data: Branch
    const IexTpMessageData* iex_tp_message_data() const;
    IexTpMessageData* iex_tp_message_data();
    void set_iex_tp_message_data(std::unique_ptr<IexTpMessageData> value);

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

    bool operator==(const SnapshotDataMessage& other) const;
    bool operator!=(const SnapshotDataMessage& other) const;

  private:
    char iex_tp_header_{};
    std::uint16_t iex_tp_message_block_length_{};
    std::uint16_t iex_tp_message_length_{};
    IexTpMessageType iex_tp_message_type_{};
    std::unique_ptr<IexTpMessageData> iex_tp_message_data_{};
};

} // namespace iex::iexequities::deepplus::snap::v1_05
