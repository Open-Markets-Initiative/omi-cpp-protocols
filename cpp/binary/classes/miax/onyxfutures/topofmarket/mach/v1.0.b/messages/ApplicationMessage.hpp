#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MessageType.hpp"
#include "../messages/Data.hpp"
#include "../messages/Message.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class Visitor;
class DataVisitor;

// Application Message
class ApplicationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = PacketType::ApplicationMessage;

    ApplicationMessage() = default;
    ApplicationMessage(const ApplicationMessage& other);
    ApplicationMessage& operator=(const ApplicationMessage& other);
    ApplicationMessage(ApplicationMessage&& other) noexcept = default;
    ApplicationMessage& operator=(ApplicationMessage&& other) noexcept = default;
    ~ApplicationMessage() = default;

    // Message Type: Code identifying this message type
    MessageType message_type_field() const;
    void set_message_type_field(MessageType value);

    // Data: Branch
    const Data* data() const;
    Data* data();
    void set_data(std::unique_ptr<Data> value);

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

    bool operator==(const ApplicationMessage& other) const;
    bool operator!=(const ApplicationMessage& other) const;

  private:
    MessageType message_type_field_{};
    std::unique_ptr<Data> data_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
