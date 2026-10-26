#include "RefreshResponseMessageApplicationMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

RefreshResponseMessageApplicationMessage::RefreshResponseMessageApplicationMessage(const RefreshResponseMessageApplicationMessage& other)
  : message_type_(other.message_type_), data_(other.data_ ? other.data_->clone() : nullptr) {}

RefreshResponseMessageApplicationMessage& RefreshResponseMessageApplicationMessage::operator=(const RefreshResponseMessageApplicationMessage& other) {
    if (this != &other) {
        message_type_ = other.message_type_;
        data_ = other.data_ ? other.data_->clone() : nullptr;
    }
    return *this;
}

MessageType RefreshResponseMessageApplicationMessage::message_type() const { return message_type_; }
void RefreshResponseMessageApplicationMessage::set_message_type(MessageType value) { message_type_ = value; }

const Data* RefreshResponseMessageApplicationMessage::data() const { return data_.get(); }
Data* RefreshResponseMessageApplicationMessage::data() { return data_.get(); }
void RefreshResponseMessageApplicationMessage::set_data(std::unique_ptr<Data> value) { data_ = std::move(value); }

std::size_t RefreshResponseMessageApplicationMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("RefreshResponseMessageApplicationMessage", offset + 1, length);
    message_type_ = static_cast<MessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = DataFactory::create(message_type_);
        offset += selected->decode(data + offset, length - offset);
        data_ = std::move(selected);
    }

    return offset;
}

std::size_t RefreshResponseMessageApplicationMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!data_) { throw EncodeError("RefreshResponseMessageApplicationMessage", "no data"); }
    wire::require_capacity("RefreshResponseMessageApplicationMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto message_type = message_type_;
    message_type = data_->type();

    wire::write_char(data + offset, static_cast<char>(message_type));
    offset += 1;

    offset += data_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t RefreshResponseMessageApplicationMessage::encoded_size() const {
    return 1 + (data_ ? data_->encoded_size() : 0);
}

void RefreshResponseMessageApplicationMessage::print(std::ostream& out) const {
    out << "RefreshResponseMessageApplicationMessage{";
    out << "message_type=";
    out << message_type_;
    out << ", data=";
    if (data_) { data_->print(out); } else { out << "null"; }
    out << '}';
}

bool RefreshResponseMessageApplicationMessage::operator==(const RefreshResponseMessageApplicationMessage& other) const {
    return message_type_ == other.message_type_
        && ((data_ == nullptr) == (other.data_ == nullptr) && (!data_ || data_->equals(*other.data_)));
}

bool RefreshResponseMessageApplicationMessage::operator!=(const RefreshResponseMessageApplicationMessage& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RefreshResponseMessageApplicationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
