#include "SummaryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"
#include "../Factory.hpp"

namespace siac::cts::output::cta::v2_9 {

SummaryMessage::SummaryMessage(const SummaryMessage& other)
  : summary_message_type_(other.summary_message_type_), summary_message_payload_(other.summary_message_payload_ ? other.summary_message_payload_->clone() : nullptr) {}

SummaryMessage& SummaryMessage::operator=(const SummaryMessage& other) {
    if (this != &other) {
        summary_message_type_ = other.summary_message_type_;
        summary_message_payload_ = other.summary_message_payload_ ? other.summary_message_payload_->clone() : nullptr;
    }
    return *this;
}

SummaryMessageType SummaryMessage::summary_message_type() const { return summary_message_type_; }
void SummaryMessage::set_summary_message_type(SummaryMessageType value) { summary_message_type_ = value; }

const SummaryMessagePayload* SummaryMessage::summary_message_payload() const { return summary_message_payload_.get(); }
SummaryMessagePayload* SummaryMessage::summary_message_payload() { return summary_message_payload_.get(); }
void SummaryMessage::set_summary_message_payload(std::unique_ptr<SummaryMessagePayload> value) { summary_message_payload_ = std::move(value); }

MessageCode SummaryMessage::type() const { return message_type; }

std::string_view SummaryMessage::name() const { return "Summary Message"; }

std::size_t SummaryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SummaryMessage", offset + 1, length);
    summary_message_type_ = static_cast<SummaryMessageType>(wire::read_char(data + offset));
    offset += 1;

    {
        auto selected = SummaryMessagePayloadFactory::create(summary_message_type_);
        offset += selected->decode(data + offset, length - offset);
        summary_message_payload_ = std::move(selected);
    }

    return offset;
}

std::size_t SummaryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    if (!summary_message_payload_) { throw EncodeError("SummaryMessage", "no summary_message_payload"); }
    wire::require_capacity("SummaryMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto summary_message_type = summary_message_type_;
    summary_message_type = summary_message_payload_->type();

    wire::write_char(data + offset, static_cast<char>(summary_message_type));
    offset += 1;

    offset += summary_message_payload_->encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SummaryMessage::encoded_size() const {
    return 1 + (summary_message_payload_ ? summary_message_payload_->encoded_size() : 0);
}

void SummaryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SummaryMessage::clone() const {
    return std::make_unique<SummaryMessage>(*this);
}

void SummaryMessage::print(std::ostream& out) const {
    out << "SummaryMessage{";
    out << "summary_message_type=";
    out << summary_message_type_;
    out << ", summary_message_payload=";
    if (summary_message_payload_) { summary_message_payload_->print(out); } else { out << "null"; }
    out << '}';
}

bool SummaryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SummaryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SummaryMessage::operator==(const SummaryMessage& other) const {
    return summary_message_type_ == other.summary_message_type_
        && ((summary_message_payload_ == nullptr) == (other.summary_message_payload_ == nullptr) && (!summary_message_payload_ || summary_message_payload_->equals(*other.summary_message_payload_)));
}

bool SummaryMessage::operator!=(const SummaryMessage& other) const {
    return !(*this == other);
}

} // namespace siac::cts::output::cta::v2_9
