#include "AuctionClearingPrice.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

AuctionClearingPrice::AuctionClearingPrice(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> last_px)
  : transact_time_(transact_time), security_id_(security_id), last_px_(last_px) {}

std::optional<std::chrono::nanoseconds> AuctionClearingPrice::transact_time() const { return transact_time_; }
void AuctionClearingPrice::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int64_t> AuctionClearingPrice::security_id() const { return security_id_; }
void AuctionClearingPrice::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> AuctionClearingPrice::last_px() const { return last_px_; }
void AuctionClearingPrice::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

MessageCode AuctionClearingPrice::type() const { return message_type; }

std::string_view AuctionClearingPrice::name() const { return "Auction Clearing Price"; }

std::size_t AuctionClearingPrice::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AuctionClearingPrice", wire_size, length);

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    security_id_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    last_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0x8000000000000000LL), -8);
    offset += 8;

    return offset;
}

std::size_t AuctionClearingPrice::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AuctionClearingPrice", wire_size, capacity);

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    wire::write_i64_le(data + offset, security_id_.value_or(static_cast<std::int64_t>(0x8000000000000000LL)));
    offset += 8;

    wire::write_i64_le(data + offset, last_px_ ? static_cast<std::int64_t>(last_px_->mantissa()) : static_cast<std::int64_t>(0x8000000000000000LL));
    offset += 8;

    return offset;
}

std::size_t AuctionClearingPrice::encoded_size() const {
    return wire_size;
}

void AuctionClearingPrice::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AuctionClearingPrice::clone() const {
    return std::make_unique<AuctionClearingPrice>(*this);
}

void AuctionClearingPrice::print(std::ostream& out) const {
    out << "AuctionClearingPrice{";
    out << "transact_time=";
    print::optional_duration(out, transact_time_);
    out << ", security_id=";
    print::optional(out, security_id_);
    out << ", last_px=";
    print::optional(out, last_px_);
    out << '}';
}

bool AuctionClearingPrice::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionClearingPrice*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionClearingPrice::operator==(const AuctionClearingPrice& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && last_px_ == other.last_px_;
}

bool AuctionClearingPrice::operator!=(const AuctionClearingPrice& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v3_0
