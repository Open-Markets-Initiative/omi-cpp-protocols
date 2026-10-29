#include "ApplicationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

ApplicationMessage::ApplicationMessage(const ApplicationMessage& other)
  : message_type_field_(other.message_type_field_), data_(other.data_ ? other.data_->clone() : nullptr) {}

ApplicationMessage& ApplicationMessage::operator=(const ApplicationMessage& other) {
    if (this != &other) {
        message_type_field_ = other.message_type_field_;
        data_ = other.data_ ? other.data_->clone() : nullptr;
    }
    return *this;
}

MessageType ApplicationMessage::message_type_field() const { return message_type_field_; }
void ApplicationMessage::set_message_type_field(MessageType value) { message_type_field_ = value; }

const Data* ApplicationMessage::data() const { return data_.get(); }
Data* ApplicationMessage::data() { return data_.get(); }
void ApplicationMessage::set_data(std::unique_ptr<Data> value) { data_ = std::move(value); }

MessageCode ApplicationMessage::type() const { return message_type; }

std::string_view ApplicationMessage::name() const { return "Application Message"; }

std::size_t ApplicationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ApplicationMessage", offset + 1, length);
    message_type_field_ = static_cast<MessageType>(wire::read_u8(data + offset));
    offset += 1;

    {
        auto selected = DataFactory::create(message_type_field_);
        offset += selected->decode(data + offset, length - offset);
        data_ = std::move(selected);
    }

    return offset;
}

std::size_t ApplicationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!data_) { throw EncodeError("ApplicationMessage", "no data"); }
    wire::require_capacity("ApplicationMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto message_type_field = message_type_field_;
    message_type_field = data_->type();

    wire::write_u8(data + offset, static_cast<std::uint8_t>(message_type_field));
    offset += 1;

    offset += data_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ApplicationMessage::encoded_size() const {
    return 1 + (data_ ? data_->encoded_size() : 0);
}

void ApplicationMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ApplicationMessage::clone() const {
    return std::make_unique<ApplicationMessage>(*this);
}

void ApplicationMessage::print(std::ostream& out) const {
    out << "ApplicationMessage{";
    out << "message_type_field=";
    out << message_type_field_;
    out << ", data=";
    if (data_) { data_->print(out); } else { out << "null"; }
    out << '}';
}

bool ApplicationMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ApplicationMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ApplicationMessage::operator==(const ApplicationMessage& other) const {
    return message_type_field_ == other.message_type_field_
        && ((data_ == nullptr) == (other.data_ == nullptr) && (!data_ || data_->equals(*other.data_)));
}

bool ApplicationMessage::operator!=(const ApplicationMessage& other) const {
    return !(*this == other);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
