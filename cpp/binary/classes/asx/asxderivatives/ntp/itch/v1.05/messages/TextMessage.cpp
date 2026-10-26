#include "TextMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

TextMessage::TextMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, const std::string& source_id, const std::string& text)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), source_id_(source_id), text_(text) {}

std::chrono::nanoseconds TextMessage::nanoseconds() const { return nanoseconds_; }
void TextMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t TextMessage::trade_date() const { return trade_date_; }
void TextMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

const std::string& TextMessage::source_id() const { return source_id_; }
std::string& TextMessage::source_id() { return source_id_; }
void TextMessage::set_source_id(const std::string& value) { source_id_ = value; }

const std::string& TextMessage::text() const { return text_; }
std::string& TextMessage::text() { return text_; }
void TextMessage::set_text(const std::string& value) { text_ = value; }

MessageCode TextMessage::type() const { return message_type; }

std::string_view TextMessage::name() const { return "Text Message"; }

std::size_t TextMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TextMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    source_id_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    text_ = wire::read_text(data + offset, 100, ' ');
    offset += 100;

    return offset;
}

std::size_t TextMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TextMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_text(data + offset, 6, ' ', source_id_);
    offset += 6;

    wire::write_text(data + offset, 100, ' ', text_);
    offset += 100;

    return offset;
}

std::size_t TextMessage::encoded_size() const {
    return wire_size;
}

void TextMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TextMessage::clone() const {
    return std::make_unique<TextMessage>(*this);
}

void TextMessage::print(std::ostream& out) const {
    out << "TextMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", source_id=";
    print::text(out, source_id_);
    out << ", text=";
    print::text(out, text_);
    out << '}';
}

bool TextMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TextMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TextMessage::operator==(const TextMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && source_id_ == other.source_id_
        && text_ == other.text_;
}

bool TextMessage::operator!=(const TextMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
