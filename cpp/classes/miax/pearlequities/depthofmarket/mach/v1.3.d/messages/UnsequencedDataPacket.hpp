#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/UnsequencedMessageType.hpp"
#include "../messages/TcpMessage.hpp"
#include "../messages/UnsequencedMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class TcpMessageVisitor;
class UnsequencedMessageVisitor;

// Each unsequenced data packet carries one unsequenced message from the higher-lever protocol
class UnsequencedDataPacket : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = EsesmPacketType::UnsequencedDataPacket;

    UnsequencedDataPacket() = default;
    UnsequencedDataPacket(const UnsequencedDataPacket& other);
    UnsequencedDataPacket& operator=(const UnsequencedDataPacket& other);
    UnsequencedDataPacket(UnsequencedDataPacket&& other) noexcept = default;
    UnsequencedDataPacket& operator=(UnsequencedDataPacket&& other) noexcept = default;
    ~UnsequencedDataPacket() = default;

    // Unsequenced Message Type: Market-data Refresh request/response discriminator carried
    // over the ESesM unsequenced channel (Request Type R, Response Type r, End of Refresh E)
    UnsequencedMessageType unsequenced_message_type() const;
    void set_unsequenced_message_type(UnsequencedMessageType value);

    // Unsequenced Message: Branch
    const UnsequencedMessage* unsequenced_message() const;
    UnsequencedMessage* unsequenced_message();
    void set_unsequenced_message(std::unique_ptr<UnsequencedMessage> value);

    // TcpMessage
    TcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TcpMessageVisitor& visitor) const override;
    std::unique_ptr<TcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TcpMessage& other) const override;

    bool operator==(const UnsequencedDataPacket& other) const;
    bool operator!=(const UnsequencedDataPacket& other) const;

  private:
    UnsequencedMessageType unsequenced_message_type_{};
    std::unique_ptr<UnsequencedMessage> unsequenced_message_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
