#include "RegShoRestrictionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

RegShoRestrictionMessage::RegShoRestrictionMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, ShortSaleRestriction short_sale_restriction)
  : timestamp_(timestamp), security_id_(security_id), short_sale_restriction_(short_sale_restriction) {}

std::chrono::nanoseconds RegShoRestrictionMessage::timestamp() const { return timestamp_; }
void RegShoRestrictionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t RegShoRestrictionMessage::security_id() const { return security_id_; }
void RegShoRestrictionMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

ShortSaleRestriction RegShoRestrictionMessage::short_sale_restriction() const { return short_sale_restriction_; }
void RegShoRestrictionMessage::set_short_sale_restriction(ShortSaleRestriction value) { short_sale_restriction_ = value; }

PayloadCode RegShoRestrictionMessage::type() const { return message_type; }

std::string_view RegShoRestrictionMessage::name() const { return "Reg Sho Restriction Message"; }

std::size_t RegShoRestrictionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RegShoRestrictionMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    short_sale_restriction_ = static_cast<ShortSaleRestriction>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t RegShoRestrictionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RegShoRestrictionMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(short_sale_restriction_));
    offset += 1;

    return offset;
}

std::size_t RegShoRestrictionMessage::encoded_size() const {
    return wire_size;
}

void RegShoRestrictionMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> RegShoRestrictionMessage::clone() const {
    return std::make_unique<RegShoRestrictionMessage>(*this);
}

void RegShoRestrictionMessage::print(std::ostream& out) const {
    out << "RegShoRestrictionMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", short_sale_restriction=";
    out << short_sale_restriction_;
    out << '}';
}

bool RegShoRestrictionMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const RegShoRestrictionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RegShoRestrictionMessage::operator==(const RegShoRestrictionMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && short_sale_restriction_ == other.short_sale_restriction_;
}

bool RegShoRestrictionMessage::operator!=(const RegShoRestrictionMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
