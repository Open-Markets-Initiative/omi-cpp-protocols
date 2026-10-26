#include "OpenInterestCategory.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::opra::output::obi::v6_2 {

OpenInterestCategory::OpenInterestCategory(const OpenInterestCategory& other)
  : open_interest_message_type_(other.open_interest_message_type_), open_interest_message_payload_(other.open_interest_message_payload_ ? other.open_interest_message_payload_->clone() : nullptr) {}

OpenInterestCategory& OpenInterestCategory::operator=(const OpenInterestCategory& other) {
    if (this != &other) {
        open_interest_message_type_ = other.open_interest_message_type_;
        open_interest_message_payload_ = other.open_interest_message_payload_ ? other.open_interest_message_payload_->clone() : nullptr;
    }
    return *this;
}

OpenInterestMessageType OpenInterestCategory::open_interest_message_type() const { return open_interest_message_type_; }
void OpenInterestCategory::set_open_interest_message_type(OpenInterestMessageType value) { open_interest_message_type_ = value; }

const OpenInterestMessagePayload* OpenInterestCategory::open_interest_message_payload() const { return open_interest_message_payload_.get(); }
OpenInterestMessagePayload* OpenInterestCategory::open_interest_message_payload() { return open_interest_message_payload_.get(); }
void OpenInterestCategory::set_open_interest_message_payload(std::unique_ptr<OpenInterestMessagePayload> value) { open_interest_message_payload_ = std::move(value); }

MessageCode OpenInterestCategory::type() const { return message_type; }

std::string_view OpenInterestCategory::name() const { return "Open Interest Category"; }

std::size_t OpenInterestCategory::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("OpenInterestCategory", offset + 1, length);
    open_interest_message_type_ = static_cast<OpenInterestMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = OpenInterestMessagePayloadFactory::create(open_interest_message_type_);
        offset += selected->decode(data + offset, length - offset);
        open_interest_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t OpenInterestCategory::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!open_interest_message_payload_) { throw EncodeError("OpenInterestCategory", "no open_interest_message_payload"); }
    wire::require_capacity("OpenInterestCategory", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto open_interest_message_type = open_interest_message_type_;
    open_interest_message_type = open_interest_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(open_interest_message_type));
    offset += 1;

    offset += open_interest_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OpenInterestCategory::encoded_size() const {
    return 1 + (open_interest_message_payload_ ? open_interest_message_payload_->encoded_size() : 0);
}

void OpenInterestCategory::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OpenInterestCategory::clone() const {
    return std::make_unique<OpenInterestCategory>(*this);
}

void OpenInterestCategory::print(std::ostream& out) const {
    out << "OpenInterestCategory{";
    out << "open_interest_message_type=";
    out << open_interest_message_type_;
    out << ", open_interest_message_payload=";
    if (open_interest_message_payload_) { open_interest_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool OpenInterestCategory::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OpenInterestCategory*>(&other);
    return that != nullptr && *this == *that;
}

bool OpenInterestCategory::operator==(const OpenInterestCategory& other) const {
    return open_interest_message_type_ == other.open_interest_message_type_
        && ((open_interest_message_payload_ == nullptr) == (other.open_interest_message_payload_ == nullptr) && (!open_interest_message_payload_ || open_interest_message_payload_->equals(*other.open_interest_message_payload_)));
}

bool OpenInterestCategory::operator!=(const OpenInterestCategory& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
