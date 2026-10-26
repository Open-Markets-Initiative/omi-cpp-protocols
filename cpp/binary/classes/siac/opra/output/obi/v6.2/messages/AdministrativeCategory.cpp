#include "AdministrativeCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

AdministrativeCategory::AdministrativeCategory(const AdministrativeCategory& other)
  : administrative_message_type_(other.administrative_message_type_), administrative_message_payload_(other.administrative_message_payload_ ? other.administrative_message_payload_->clone() : nullptr) {}

AdministrativeCategory& AdministrativeCategory::operator=(const AdministrativeCategory& other) {
    if (this != &other) {
        administrative_message_type_ = other.administrative_message_type_;
        administrative_message_payload_ = other.administrative_message_payload_ ? other.administrative_message_payload_->clone() : nullptr;
    }
    return *this;
}

AdministrativeMessageType AdministrativeCategory::administrative_message_type() const { return administrative_message_type_; }
void AdministrativeCategory::set_administrative_message_type(AdministrativeMessageType value) { administrative_message_type_ = value; }

const AdministrativeMessagePayload* AdministrativeCategory::administrative_message_payload() const { return administrative_message_payload_.get(); }
AdministrativeMessagePayload* AdministrativeCategory::administrative_message_payload() { return administrative_message_payload_.get(); }
void AdministrativeCategory::set_administrative_message_payload(std::unique_ptr<AdministrativeMessagePayload> value) { administrative_message_payload_ = std::move(value); }

MessageCode AdministrativeCategory::type() const { return message_type; }

std::string_view AdministrativeCategory::name() const { return "Administrative Category"; }

std::size_t AdministrativeCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("AdministrativeCategory", offset + 1, length);
    administrative_message_type_ = static_cast<AdministrativeMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = AdministrativeMessagePayloadFactory::create(administrative_message_type_);
        offset += selected->decode(data + offset, length - offset);
        administrative_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t AdministrativeCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!administrative_message_payload_) { throw EncodeError("AdministrativeCategory", "no administrative_message_payload"); }
    wire::require_capacity("AdministrativeCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto administrative_message_type = administrative_message_type_;
    administrative_message_type = administrative_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(administrative_message_type));
    offset += 1;

    offset += administrative_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t AdministrativeCategory::encoded_size() const {
    return 1 + (administrative_message_payload_ ? administrative_message_payload_->encoded_size() : 0);
}

void AdministrativeCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AdministrativeCategory::clone() const {
    return std::make_unique<AdministrativeCategory>(*this);
}

void AdministrativeCategory::print(std::ostream& out) const {
    out << "AdministrativeCategory{";
    out << "administrative_message_type=";
    out << administrative_message_type_;
    out << ", administrative_message_payload=";
    if (administrative_message_payload_) { administrative_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool AdministrativeCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AdministrativeCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool AdministrativeCategory::operator==(const AdministrativeCategory& other) const {
    return administrative_message_type_ == other.administrative_message_type_
        && ((administrative_message_payload_ == nullptr) == (other.administrative_message_payload_ == nullptr) && (!administrative_message_payload_ || administrative_message_payload_->equals(*other.administrative_message_payload_)));
}

bool AdministrativeCategory::operator!=(const AdministrativeCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
