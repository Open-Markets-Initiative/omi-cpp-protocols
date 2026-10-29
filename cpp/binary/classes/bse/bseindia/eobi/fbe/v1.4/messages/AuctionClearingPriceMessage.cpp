#include "AuctionClearingPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

AuctionClearingPriceMessage::AuctionClearingPriceMessage(std::chrono::nanoseconds transact_time, std::int64_t security_id, Decimal last_px, std::int64_t last_qty)
  : transact_time_(transact_time), security_id_(security_id), last_px_(last_px), last_qty_(last_qty) {}

std::chrono::nanoseconds AuctionClearingPriceMessage::transact_time() const { return transact_time_; }
void AuctionClearingPriceMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::int64_t AuctionClearingPriceMessage::security_id() const { return security_id_; }
void AuctionClearingPriceMessage::set_security_id(std::int64_t value) { security_id_ = value; }

Decimal AuctionClearingPriceMessage::last_px() const { return last_px_; }
void AuctionClearingPriceMessage::set_last_px(Decimal value) { last_px_ = value; }

std::int64_t AuctionClearingPriceMessage::last_qty() const { return last_qty_; }
void AuctionClearingPriceMessage::set_last_qty(std::int64_t value) { last_qty_ = value; }

MessageCode AuctionClearingPriceMessage::type() const { return message_type; }

std::string_view AuctionClearingPriceMessage::name() const { return "Auction Clearing Price Message"; }

std::size_t AuctionClearingPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionClearingPriceMessage", wire_size, length);

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_id_ = wire::read_i64_le(data + offset);
    offset += 8;

    last_px_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    last_qty_ = wire::read_i64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t AuctionClearingPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionClearingPriceMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_px_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(last_qty_));
    offset += 8;

    return offset;
}

std::size_t AuctionClearingPriceMessage::encoded_size() const {
    return wire_size;
}

void AuctionClearingPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionClearingPriceMessage::clone() const {
    return std::make_unique<AuctionClearingPriceMessage>(*this);
}

void AuctionClearingPriceMessage::print(std::ostream& out) const {
    out << "AuctionClearingPriceMessage{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", last_px=";
    out << last_px_;
    out << ", last_qty=";
    out << last_qty_;
    out << '}';
}

bool AuctionClearingPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionClearingPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionClearingPriceMessage::operator==(const AuctionClearingPriceMessage& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && last_px_ == other.last_px_
        && last_qty_ == other.last_qty_;
}

bool AuctionClearingPriceMessage::operator!=(const AuctionClearingPriceMessage& other) const {
    return !(*this == other);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
