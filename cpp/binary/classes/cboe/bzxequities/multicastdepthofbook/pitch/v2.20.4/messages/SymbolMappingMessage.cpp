#include "SymbolMappingMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

SymbolMappingMessage::SymbolMappingMessage(const std::string& feed_symbol, const std::string& osi_symbol, SymbolCondition symbol_condition)
  : feed_symbol_(feed_symbol), osi_symbol_(osi_symbol), symbol_condition_(symbol_condition) {}

const std::string& SymbolMappingMessage::feed_symbol() const { return feed_symbol_; }
std::string& SymbolMappingMessage::feed_symbol() { return feed_symbol_; }
void SymbolMappingMessage::set_feed_symbol(const std::string& value) { feed_symbol_ = value; }

const std::string& SymbolMappingMessage::osi_symbol() const { return osi_symbol_; }
std::string& SymbolMappingMessage::osi_symbol() { return osi_symbol_; }
void SymbolMappingMessage::set_osi_symbol(const std::string& value) { osi_symbol_ = value; }

SymbolCondition SymbolMappingMessage::symbol_condition() const { return symbol_condition_; }
void SymbolMappingMessage::set_symbol_condition(SymbolCondition value) { symbol_condition_ = value; }

MessageCode SymbolMappingMessage::type() const { return message_type; }

std::string_view SymbolMappingMessage::name() const { return "Symbol Mapping Message"; }

std::size_t SymbolMappingMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SymbolMappingMessage", wire_size, length);

    feed_symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    osi_symbol_ = wire::read_text(data + offset, 21, ' ');
    offset += 21;

    symbol_condition_ = static_cast<SymbolCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SymbolMappingMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SymbolMappingMessage", wire_size, capacity);

    wire::write_text(data + offset, 6, ' ', feed_symbol_);
    offset += 6;

    wire::write_text(data + offset, 21, ' ', osi_symbol_);
    offset += 21;

    wire::write_char(data + offset, static_cast<char>(symbol_condition_));
    offset += 1;

    return offset;
}

std::size_t SymbolMappingMessage::encoded_size() const {
    return wire_size;
}

void SymbolMappingMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SymbolMappingMessage::clone() const {
    return std::make_unique<SymbolMappingMessage>(*this);
}

void SymbolMappingMessage::print(std::ostream& out) const {
    out << "SymbolMappingMessage{";
    out << "feed_symbol=";
    print::text(out, feed_symbol_);
    out << ", osi_symbol=";
    print::text(out, osi_symbol_);
    out << ", symbol_condition=";
    out << symbol_condition_;
    out << '}';
}

bool SymbolMappingMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SymbolMappingMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SymbolMappingMessage::operator==(const SymbolMappingMessage& other) const {
    return feed_symbol_ == other.feed_symbol_
        && osi_symbol_ == other.osi_symbol_
        && symbol_condition_ == other.symbol_condition_;
}

bool SymbolMappingMessage::operator!=(const SymbolMappingMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
