#include "EndOfRefreshNotificationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

EndOfRefreshNotificationMessage::EndOfRefreshNotificationMessage(RefreshMessageType refresh_message_type)
  : refresh_message_type_(refresh_message_type) {}

RefreshMessageType EndOfRefreshNotificationMessage::refresh_message_type() const { return refresh_message_type_; }
void EndOfRefreshNotificationMessage::set_refresh_message_type(RefreshMessageType value) { refresh_message_type_ = value; }

UnsequencedMessageCode EndOfRefreshNotificationMessage::type() const { return message_type; }

std::string_view EndOfRefreshNotificationMessage::name() const { return "End Of Refresh Notification Message"; }

std::size_t EndOfRefreshNotificationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfRefreshNotificationMessage", wire_size, length);

    refresh_message_type_ = static_cast<RefreshMessageType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t EndOfRefreshNotificationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfRefreshNotificationMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(refresh_message_type_));
    offset += 1;

    return offset;
}

std::size_t EndOfRefreshNotificationMessage::encoded_size() const {
    return wire_size;
}

void EndOfRefreshNotificationMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> EndOfRefreshNotificationMessage::clone() const {
    return std::make_unique<EndOfRefreshNotificationMessage>(*this);
}

void EndOfRefreshNotificationMessage::print(std::ostream& out) const {
    out << "EndOfRefreshNotificationMessage{";
    out << "refresh_message_type=";
    out << refresh_message_type_;
    out << '}';
}

bool EndOfRefreshNotificationMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const EndOfRefreshNotificationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfRefreshNotificationMessage::operator==(const EndOfRefreshNotificationMessage& other) const {
    return refresh_message_type_ == other.refresh_message_type_;
}

bool EndOfRefreshNotificationMessage::operator!=(const EndOfRefreshNotificationMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
