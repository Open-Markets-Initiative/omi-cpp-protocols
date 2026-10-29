#include "AuctionBbo.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

AuctionBbo::AuctionBbo(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> bid_px, std::optional<Decimal> offer_px)
  : transact_time_(transact_time), security_id_(security_id), bid_px_(bid_px), offer_px_(offer_px) {}

std::optional<std::chrono::nanoseconds> AuctionBbo::transact_time() const { return transact_time_; }
void AuctionBbo::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int64_t> AuctionBbo::security_id() const { return security_id_; }
void AuctionBbo::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> AuctionBbo::bid_px() const { return bid_px_; }
void AuctionBbo::set_bid_px(std::optional<Decimal> value) { bid_px_ = value; }

std::optional<Decimal> AuctionBbo::offer_px() const { return offer_px_; }
void AuctionBbo::set_offer_px(std::optional<Decimal> value) { offer_px_ = value; }

MessageCode AuctionBbo::type() const { return message_type; }

std::string_view AuctionBbo::name() const { return "Auction Bbo"; }

std::size_t AuctionBbo::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionBbo", wire_size, length);

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    bid_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    offer_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t AuctionBbo::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionBbo", wire_size, capacity);

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, bid_px_ ? static_cast<std::int64_t>(bid_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    wire::write_i64_le(data + offset, offer_px_ ? static_cast<std::int64_t>(offer_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t AuctionBbo::encoded_size() const {
    return wire_size;
}

void AuctionBbo::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionBbo::clone() const {
    return std::make_unique<AuctionBbo>(*this);
}

void AuctionBbo::print(std::ostream& out) const {
    out << "AuctionBbo{";
    out << "transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", bid_px=";
    print::optional(out, bid_px_);
    out << ", offer_px=";
    print::optional(out, offer_px_);
    out << '}';
}

bool AuctionBbo::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionBbo*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionBbo::operator==(const AuctionBbo& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && bid_px_ == other.bid_px_
        && offer_px_ == other.offer_px_;
}

bool AuctionBbo::operator!=(const AuctionBbo& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
