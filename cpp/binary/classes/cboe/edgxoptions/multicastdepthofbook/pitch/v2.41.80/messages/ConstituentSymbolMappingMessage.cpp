#include "ConstituentSymbolMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

ConstituentSymbolMappingMessage::ConstituentSymbolMappingMessage(const std::string& feed_symbol, const std::string& osi_symbol, SymbolCondition symbol_condition, const std::string& underlying, const std::string& soq_identifier)
  : feed_symbol_(feed_symbol), osi_symbol_(osi_symbol), symbol_condition_(symbol_condition), underlying_(underlying), soq_identifier_(soq_identifier) {}

const std::string& ConstituentSymbolMappingMessage::feed_symbol() const { return feed_symbol_; }
std::string& ConstituentSymbolMappingMessage::feed_symbol() { return feed_symbol_; }
void ConstituentSymbolMappingMessage::set_feed_symbol(const std::string& value) { feed_symbol_ = value; }

const std::string& ConstituentSymbolMappingMessage::osi_symbol() const { return osi_symbol_; }
std::string& ConstituentSymbolMappingMessage::osi_symbol() { return osi_symbol_; }
void ConstituentSymbolMappingMessage::set_osi_symbol(const std::string& value) { osi_symbol_ = value; }

SymbolCondition ConstituentSymbolMappingMessage::symbol_condition() const { return symbol_condition_; }
void ConstituentSymbolMappingMessage::set_symbol_condition(SymbolCondition value) { symbol_condition_ = value; }

const std::string& ConstituentSymbolMappingMessage::underlying() const { return underlying_; }
std::string& ConstituentSymbolMappingMessage::underlying() { return underlying_; }
void ConstituentSymbolMappingMessage::set_underlying(const std::string& value) { underlying_ = value; }

const std::string& ConstituentSymbolMappingMessage::soq_identifier() const { return soq_identifier_; }
std::string& ConstituentSymbolMappingMessage::soq_identifier() { return soq_identifier_; }
void ConstituentSymbolMappingMessage::set_soq_identifier(const std::string& value) { soq_identifier_ = value; }

MessageCode ConstituentSymbolMappingMessage::type() const { return message_type; }

std::string_view ConstituentSymbolMappingMessage::name() const { return "Constituent Symbol Mapping Message"; }

std::size_t ConstituentSymbolMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ConstituentSymbolMappingMessage", wire_size, length);

    feed_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    osi_symbol_ = wire::read_text(data + offset, 21, ' ');
    offset += 21;

    symbol_condition_ = static_cast<SymbolCondition>(wire::read_char(data + offset));
    offset += 1;

    underlying_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    soq_identifier_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    return offset;
}

std::size_t ConstituentSymbolMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ConstituentSymbolMappingMessage", wire_size, capacity);

    wire::write_text(data + offset, 6, ' ', feed_symbol_);
    offset += 6;

    wire::write_text(data + offset, 21, ' ', osi_symbol_);
    offset += 21;

    wire::write_char(data + offset, static_cast<char>(symbol_condition_));
    offset += 1;

    wire::write_text(data + offset, 8, ' ', underlying_);
    offset += 8;

    wire::write_text(data + offset, 20, ' ', soq_identifier_);
    offset += 20;

    return offset;
}

std::size_t ConstituentSymbolMappingMessage::encoded_size() const {
    return wire_size;
}

void ConstituentSymbolMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ConstituentSymbolMappingMessage::clone() const {
    return std::make_unique<ConstituentSymbolMappingMessage>(*this);
}

void ConstituentSymbolMappingMessage::print(std::ostream& out) const {
    out << "ConstituentSymbolMappingMessage{";
    out << "feed_symbol=";
    print::text(out, feed_symbol_);
    out << ", osi_symbol=";
    print::text(out, osi_symbol_);
    out << ", symbol_condition=";
    out << symbol_condition_;
    out << ", underlying=";
    print::text(out, underlying_);
    out << ", soq_identifier=";
    print::text(out, soq_identifier_);
    out << '}';
}

bool ConstituentSymbolMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ConstituentSymbolMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ConstituentSymbolMappingMessage::operator==(const ConstituentSymbolMappingMessage& other) const {
    return feed_symbol_ == other.feed_symbol_
        && osi_symbol_ == other.osi_symbol_
        && symbol_condition_ == other.symbol_condition_
        && underlying_ == other.underlying_
        && soq_identifier_ == other.soq_identifier_;
}

bool ConstituentSymbolMappingMessage::operator!=(const ConstituentSymbolMappingMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
