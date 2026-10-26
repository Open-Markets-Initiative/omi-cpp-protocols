#include "SoqStrikeRangeUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

SoqStrikeRangeUpdateMessage::SoqStrikeRangeUpdateMessage(std::chrono::nanoseconds time_offset, const std::string& soq_identifier, Decimal lower_strike_price, Decimal upper_strike_price)
  : time_offset_(time_offset), soq_identifier_(soq_identifier), lower_strike_price_(lower_strike_price), upper_strike_price_(upper_strike_price) {}

std::chrono::nanoseconds SoqStrikeRangeUpdateMessage::time_offset() const { return time_offset_; }
void SoqStrikeRangeUpdateMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& SoqStrikeRangeUpdateMessage::soq_identifier() const { return soq_identifier_; }
std::string& SoqStrikeRangeUpdateMessage::soq_identifier() { return soq_identifier_; }
void SoqStrikeRangeUpdateMessage::set_soq_identifier(const std::string& value) { soq_identifier_ = value; }

Decimal SoqStrikeRangeUpdateMessage::lower_strike_price() const { return lower_strike_price_; }
void SoqStrikeRangeUpdateMessage::set_lower_strike_price(Decimal value) { lower_strike_price_ = value; }

Decimal SoqStrikeRangeUpdateMessage::upper_strike_price() const { return upper_strike_price_; }
void SoqStrikeRangeUpdateMessage::set_upper_strike_price(Decimal value) { upper_strike_price_ = value; }

MessageCode SoqStrikeRangeUpdateMessage::type() const { return message_type; }

std::string_view SoqStrikeRangeUpdateMessage::name() const { return "Soq Strike Range Update Message"; }

std::size_t SoqStrikeRangeUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SoqStrikeRangeUpdateMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    soq_identifier_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    lower_strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    upper_strike_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t SoqStrikeRangeUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SoqStrikeRangeUpdateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 20, ' ', soq_identifier_);
    offset += 20;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(lower_strike_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(upper_strike_price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t SoqStrikeRangeUpdateMessage::encoded_size() const {
    return wire_size;
}

void SoqStrikeRangeUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SoqStrikeRangeUpdateMessage::clone() const {
    return std::make_unique<SoqStrikeRangeUpdateMessage>(*this);
}

void SoqStrikeRangeUpdateMessage::print(std::ostream& out) const {
    out << "SoqStrikeRangeUpdateMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", soq_identifier=";
    print::text(out, soq_identifier_);
    out << ", lower_strike_price=";
    out << lower_strike_price_;
    out << ", upper_strike_price=";
    out << upper_strike_price_;
    out << '}';
}

bool SoqStrikeRangeUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SoqStrikeRangeUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SoqStrikeRangeUpdateMessage::operator==(const SoqStrikeRangeUpdateMessage& other) const {
    return time_offset_ == other.time_offset_
        && soq_identifier_ == other.soq_identifier_
        && lower_strike_price_ == other.lower_strike_price_
        && upper_strike_price_ == other.upper_strike_price_;
}

bool SoqStrikeRangeUpdateMessage::operator!=(const SoqStrikeRangeUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
