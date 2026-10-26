#include "MessageResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

MessageResponseMessage::MessageResponseMessage(const std::array<std::byte, 0>& data)
  : data_(data) {}

const std::array<std::byte, 0>& MessageResponseMessage::data() const { return data_; }
std::array<std::byte, 0>& MessageResponseMessage::data() { return data_; }
void MessageResponseMessage::set_data(const std::array<std::byte, 0>& value) { data_ = value; }

TcpMessageCode MessageResponseMessage::type() const { return message_type; }

std::string_view MessageResponseMessage::name() const { return "Message Response Message"; }

std::size_t MessageResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("MessageResponseMessage", wire_size, length);

    wire::read_bytes(data + offset, data_.data(), 0);
    offset += 0;

    return offset;
}

std::size_t MessageResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MessageResponseMessage", wire_size, capacity);

    wire::write_bytes(data + offset, data_.data(), 0);
    offset += 0;

    return offset;
}

std::size_t MessageResponseMessage::encoded_size() const {
    return wire_size;
}

void MessageResponseMessage::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> MessageResponseMessage::clone() const {
    return std::make_unique<MessageResponseMessage>(*this);
}

void MessageResponseMessage::print(std::ostream& out) const {
    out << "MessageResponseMessage{";
    out << "data=";
    print::hex(out, data_.data(), data_.size());
    out << '}';
}

bool MessageResponseMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const MessageResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool MessageResponseMessage::operator==(const MessageResponseMessage& other) const {
    return data_ == other.data_;
}

bool MessageResponseMessage::operator!=(const MessageResponseMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
