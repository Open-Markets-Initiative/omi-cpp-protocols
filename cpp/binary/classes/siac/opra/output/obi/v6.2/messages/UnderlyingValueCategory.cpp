#include "UnderlyingValueCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

UnderlyingValueCategory::UnderlyingValueCategory(const UnderlyingValueCategory& other)
  : underlying_value_message_type_(other.underlying_value_message_type_), underlying_value_message_payload_(other.underlying_value_message_payload_ ? other.underlying_value_message_payload_->clone() : nullptr) {}

UnderlyingValueCategory& UnderlyingValueCategory::operator=(const UnderlyingValueCategory& other) {
    if (this != &other) {
        underlying_value_message_type_ = other.underlying_value_message_type_;
        underlying_value_message_payload_ = other.underlying_value_message_payload_ ? other.underlying_value_message_payload_->clone() : nullptr;
    }
    return *this;
}

UnderlyingValueMessageType UnderlyingValueCategory::underlying_value_message_type() const { return underlying_value_message_type_; }
void UnderlyingValueCategory::set_underlying_value_message_type(UnderlyingValueMessageType value) { underlying_value_message_type_ = value; }

const UnderlyingValueMessagePayload* UnderlyingValueCategory::underlying_value_message_payload() const { return underlying_value_message_payload_.get(); }
UnderlyingValueMessagePayload* UnderlyingValueCategory::underlying_value_message_payload() { return underlying_value_message_payload_.get(); }
void UnderlyingValueCategory::set_underlying_value_message_payload(std::unique_ptr<UnderlyingValueMessagePayload> value) { underlying_value_message_payload_ = std::move(value); }

MessageCode UnderlyingValueCategory::type() const { return message_type; }

std::string_view UnderlyingValueCategory::name() const { return "Underlying Value Category"; }

std::size_t UnderlyingValueCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("UnderlyingValueCategory", offset + 1, length);
    underlying_value_message_type_ = static_cast<UnderlyingValueMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = UnderlyingValueMessagePayloadFactory::create(underlying_value_message_type_);
        offset += selected->decode(data + offset, length - offset);
        underlying_value_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t UnderlyingValueCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!underlying_value_message_payload_) { throw EncodeError("UnderlyingValueCategory", "no underlying_value_message_payload"); }
    wire::require_capacity("UnderlyingValueCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto underlying_value_message_type = underlying_value_message_type_;
    underlying_value_message_type = underlying_value_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(underlying_value_message_type));
    offset += 1;

    offset += underlying_value_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t UnderlyingValueCategory::encoded_size() const {
    return 1 + (underlying_value_message_payload_ ? underlying_value_message_payload_->encoded_size() : 0);
}

void UnderlyingValueCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> UnderlyingValueCategory::clone() const {
    return std::make_unique<UnderlyingValueCategory>(*this);
}

void UnderlyingValueCategory::print(std::ostream& out) const {
    out << "UnderlyingValueCategory{";
    out << "underlying_value_message_type=";
    out << underlying_value_message_type_;
    out << ", underlying_value_message_payload=";
    if (underlying_value_message_payload_) { underlying_value_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool UnderlyingValueCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnderlyingValueCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool UnderlyingValueCategory::operator==(const UnderlyingValueCategory& other) const {
    return underlying_value_message_type_ == other.underlying_value_message_type_
        && ((underlying_value_message_payload_ == nullptr) == (other.underlying_value_message_payload_ == nullptr) && (!underlying_value_message_payload_ || underlying_value_message_payload_->equals(*other.underlying_value_message_payload_)));
}

bool UnderlyingValueCategory::operator!=(const UnderlyingValueCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
