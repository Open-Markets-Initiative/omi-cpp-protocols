#include "TopOfBookMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

TopOfBookMessage::TopOfBookMessage(std::chrono::nanoseconds transact_time, std::int64_t security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px)
  : transact_time_(transact_time), security_id_(security_id), bid_px_(bid_px), offer_px_(offer_px) {}

std::chrono::nanoseconds TopOfBookMessage::transact_time() const { return transact_time_; }
void TopOfBookMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::int64_t TopOfBookMessage::security_id() const { return security_id_; }
void TopOfBookMessage::set_security_id(std::int64_t value) { security_id_ = value; }

std::optional<Decimal> TopOfBookMessage::bid_px() const { return bid_px_; }
void TopOfBookMessage::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> TopOfBookMessage::offer_px() const { return offer_px_; }
void TopOfBookMessage::set_offer_px(std::optional<Decimal> value) { offer_px_ = value; }

MessageCode TopOfBookMessage::type() const { return message_type; }

std::string_view TopOfBookMessage::name() const { return "Top Of Book Message"; }

std::size_t TopOfBookMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TopOfBookMessage", wire_size, length);

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    bid_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    offer_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -6);
    offset += 8;

    return offset;
}

std::size_t TopOfBookMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TopOfBookMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, bid_px_ ? static_cast<std::int64_t>(bid_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, offer_px_ ? static_cast<std::int64_t>(offer_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t TopOfBookMessage::encoded_size() const {
    return wire_size;
}

void TopOfBookMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TopOfBookMessage::clone() const {
    return std::make_unique<TopOfBookMessage>(*this);
}

void TopOfBookMessage::print(std::ostream& out) const {
    out << "TopOfBookMessage{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", bid_px=";
    print::optional(out, bid_px_);
    out << ", offer_px=";
    print::optional(out, offer_px_);
    out << '}';
}

bool TopOfBookMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TopOfBookMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TopOfBookMessage::operator==(const TopOfBookMessage& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && bid_px_ == other.bid_px_
        && offer_px_ == other.offer_px_;
}

bool TopOfBookMessage::operator!=(const TopOfBookMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
