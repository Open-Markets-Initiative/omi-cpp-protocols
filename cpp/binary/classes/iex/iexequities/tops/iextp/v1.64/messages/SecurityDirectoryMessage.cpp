#include "SecurityDirectoryMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

SecurityDirectoryMessage::SecurityDirectoryMessage(const SecurityDirectoryFlags& security_directory_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t round_lot_size, Decimal adjusted_poc_price, LuldTier luld_tier)
  : security_directory_flags_(security_directory_flags), timestamp_(timestamp), symbol_(symbol), round_lot_size_(round_lot_size), adjusted_poc_price_(adjusted_poc_price), luld_tier_(luld_tier) {}

const SecurityDirectoryFlags& SecurityDirectoryMessage::security_directory_flags() const { return security_directory_flags_; }
SecurityDirectoryFlags& SecurityDirectoryMessage::security_directory_flags() { return security_directory_flags_; }
void SecurityDirectoryMessage::set_security_directory_flags(const SecurityDirectoryFlags& value) { security_directory_flags_ = value; }

std::chrono::nanoseconds SecurityDirectoryMessage::timestamp() const { return timestamp_; }
void SecurityDirectoryMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& SecurityDirectoryMessage::symbol() const { return symbol_; }
std::string& SecurityDirectoryMessage::symbol() { return symbol_; }
void SecurityDirectoryMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t SecurityDirectoryMessage::round_lot_size() const { return round_lot_size_; }
void SecurityDirectoryMessage::set_round_lot_size(std::uint32_t value) { round_lot_size_ = value; }

Decimal SecurityDirectoryMessage::adjusted_poc_price() const { return adjusted_poc_price_; }
void SecurityDirectoryMessage::set_adjusted_poc_price(Decimal value) { adjusted_poc_price_ = value; }

LuldTier SecurityDirectoryMessage::luld_tier() const { return luld_tier_; }
void SecurityDirectoryMessage::set_luld_tier(LuldTier value) { luld_tier_ = value; }

MessageCode SecurityDirectoryMessage::type() const { return message_type; }

std::string_view SecurityDirectoryMessage::name() const { return "Security Directory Message"; }

std::size_t SecurityDirectoryMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityDirectoryMessage", wire_size, length);

    offset += security_directory_flags_.decode(data + offset, length - offset);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    round_lot_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    adjusted_poc_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    luld_tier_ = static_cast<LuldTier>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t SecurityDirectoryMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDirectoryMessage", wire_size, capacity);

    offset += security_directory_flags_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(round_lot_size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(adjusted_poc_price_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(luld_tier_));
    offset += 1;

    return offset;
}

std::size_t SecurityDirectoryMessage::encoded_size() const {
    return wire_size;
}

void SecurityDirectoryMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityDirectoryMessage::clone() const {
    return std::make_unique<SecurityDirectoryMessage>(*this);
}

void SecurityDirectoryMessage::print(std::ostream& out) const {
    out << "SecurityDirectoryMessage{";
    out << "security_directory_flags=";
    security_directory_flags_.print(out);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", round_lot_size=";
    out << round_lot_size_;
    out << ", adjusted_poc_price=";
    out << adjusted_poc_price_;
    out << ", luld_tier=";
    out << luld_tier_;
    out << '}';
}

bool SecurityDirectoryMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityDirectoryMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityDirectoryMessage::operator==(const SecurityDirectoryMessage& other) const {
    return security_directory_flags_ == other.security_directory_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && round_lot_size_ == other.round_lot_size_
        && adjusted_poc_price_ == other.adjusted_poc_price_
        && luld_tier_ == other.luld_tier_;
}

bool SecurityDirectoryMessage::operator!=(const SecurityDirectoryMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::iextp::v1_64
