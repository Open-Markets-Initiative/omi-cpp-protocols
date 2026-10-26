#include "PriorDayMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v2_11_b {

PriorDayMessage::PriorDayMessage(const PriorDayMessage& other)
  : prior_day_message_type_(other.prior_day_message_type_), prior_day_message_payload_(other.prior_day_message_payload_ ? other.prior_day_message_payload_->clone() : nullptr) {}

PriorDayMessage& PriorDayMessage::operator=(const PriorDayMessage& other) {
    if (this != &other) {
        prior_day_message_type_ = other.prior_day_message_type_;
        prior_day_message_payload_ = other.prior_day_message_payload_ ? other.prior_day_message_payload_->clone() : nullptr;
    }
    return *this;
}

PriorDayMessageType PriorDayMessage::prior_day_message_type() const { return prior_day_message_type_; }
void PriorDayMessage::set_prior_day_message_type(PriorDayMessageType value) { prior_day_message_type_ = value; }

const PriorDayMessagePayload* PriorDayMessage::prior_day_message_payload() const { return prior_day_message_payload_.get(); }
PriorDayMessagePayload* PriorDayMessage::prior_day_message_payload() { return prior_day_message_payload_.get(); }
void PriorDayMessage::set_prior_day_message_payload(std::unique_ptr<PriorDayMessagePayload> value) { prior_day_message_payload_ = std::move(value); }

MessageCode PriorDayMessage::type() const { return message_type; }

std::string_view PriorDayMessage::name() const { return "Prior Day Message"; }

std::size_t PriorDayMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("PriorDayMessage", offset + 1, length);
    prior_day_message_type_ = static_cast<PriorDayMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = PriorDayMessagePayloadFactory::create(prior_day_message_type_);
        offset += selected->decode(data + offset, length - offset);
        prior_day_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t PriorDayMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!prior_day_message_payload_) { throw EncodeError("PriorDayMessage", "no prior_day_message_payload"); }
    wire::require_capacity("PriorDayMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto prior_day_message_type = prior_day_message_type_;
    prior_day_message_type = prior_day_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(prior_day_message_type));
    offset += 1;

    offset += prior_day_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PriorDayMessage::encoded_size() const {
    return 1 + (prior_day_message_payload_ ? prior_day_message_payload_->encoded_size() : 0);
}

void PriorDayMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriorDayMessage::clone() const {
    return std::make_unique<PriorDayMessage>(*this);
}

void PriorDayMessage::print(std::ostream& out) const {
    out << "PriorDayMessage{";
    out << "prior_day_message_type=";
    out << prior_day_message_type_;
    out << ", prior_day_message_payload=";
    if (prior_day_message_payload_) { prior_day_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool PriorDayMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriorDayMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriorDayMessage::operator==(const PriorDayMessage& other) const {
    return prior_day_message_type_ == other.prior_day_message_type_
        && ((prior_day_message_payload_ == nullptr) == (other.prior_day_message_payload_ == nullptr) && (!prior_day_message_payload_ || prior_day_message_payload_->equals(*other.prior_day_message_payload_)));
}

bool PriorDayMessage::operator!=(const PriorDayMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_11_b
