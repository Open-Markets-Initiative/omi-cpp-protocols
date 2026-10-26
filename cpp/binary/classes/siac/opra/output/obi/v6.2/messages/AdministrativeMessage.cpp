#include "AdministrativeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

AdministrativeMessage::AdministrativeMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, std::uint16_t message_data_length, const std::string& message_data)
  : message_indicator_(message_indicator), transaction_id_(transaction_id), participant_reference_number_(participant_reference_number), message_data_length_(message_data_length), message_data_(message_data) {}

char AdministrativeMessage::message_indicator() const { return message_indicator_; }
void AdministrativeMessage::set_message_indicator(char value) { message_indicator_ = value; }

std::uint32_t AdministrativeMessage::transaction_id() const { return transaction_id_; }
void AdministrativeMessage::set_transaction_id(std::uint32_t value) { transaction_id_ = value; }

std::uint32_t AdministrativeMessage::participant_reference_number() const { return participant_reference_number_; }
void AdministrativeMessage::set_participant_reference_number(std::uint32_t value) { participant_reference_number_ = value; }

std::uint16_t AdministrativeMessage::message_data_length() const { return message_data_length_; }
void AdministrativeMessage::set_message_data_length(std::uint16_t value) { message_data_length_ = value; }

const std::string& AdministrativeMessage::message_data() const { return message_data_; }
std::string& AdministrativeMessage::message_data() { return message_data_; }
void AdministrativeMessage::set_message_data(const std::string& value) { message_data_ = value; }

AdministrativeMessagePayloadCode AdministrativeMessage::type() const { return message_type; }

std::string_view AdministrativeMessage::name() const { return "Administrative Message"; }

std::size_t AdministrativeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("AdministrativeMessage", offset + 1, length);
    message_indicator_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("AdministrativeMessage", offset + 4, length);
    transaction_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("AdministrativeMessage", offset + 4, length);
    participant_reference_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    wire::require("AdministrativeMessage", offset + 2, length);
    message_data_length_ = wire::read_u16_be(data + offset);
    offset += 2;

    {
        const std::size_t count = wire::count(message_data_length_);
        wire::require("AdministrativeMessage", offset + count, length);
        message_data_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t AdministrativeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdministrativeMessage", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto message_data_length = message_data_length_;
    message_data_length = static_cast<std::uint16_t>(message_data_.size());

    wire::write_char(data + offset, message_indicator_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(transaction_id_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(participant_reference_number_));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(message_data_length));
    offset += 2;

    wire::require_capacity("encode", offset + message_data_.size(), capacity);
    wire::write_text(data + offset, message_data_.size(), ' ', message_data_);
    offset += message_data_.size();

    return offset;
}

std::size_t AdministrativeMessage::encoded_size() const {
    return 1 + 4 + 4 + 2 + message_data_.size();
}

void AdministrativeMessage::accept(AdministrativeMessagePayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<AdministrativeMessagePayload> AdministrativeMessage::clone() const {
    return std::make_unique<AdministrativeMessage>(*this);
}

void AdministrativeMessage::print(std::ostream& out) const {
    out << "AdministrativeMessage{";
    out << "message_indicator=";
    print::character(out, message_indicator_);
    out << ", transaction_id=";
    out << transaction_id_;
    out << ", participant_reference_number=";
    out << participant_reference_number_;
    out << ", message_data_length=";
    out << message_data_length_;
    out << ", message_data=";
    print::text(out, message_data_);
    out << '}';
}

bool AdministrativeMessage::equals(const AdministrativeMessagePayload& other) const {
    const auto* that = dynamic_cast<const AdministrativeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AdministrativeMessage::operator==(const AdministrativeMessage& other) const {
    return message_indicator_ == other.message_indicator_
        && transaction_id_ == other.transaction_id_
        && participant_reference_number_ == other.participant_reference_number_
        && message_data_length_ == other.message_data_length_
        && message_data_ == other.message_data_;
}

bool AdministrativeMessage::operator!=(const AdministrativeMessage& other) const {
    return !(*this == other);
}

} // namespace siac::opra::output::obi::v6_2
