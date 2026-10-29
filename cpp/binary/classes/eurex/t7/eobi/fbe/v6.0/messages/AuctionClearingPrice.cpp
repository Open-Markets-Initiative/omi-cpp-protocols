#include "AuctionClearingPrice.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

AuctionClearingPrice::AuctionClearingPrice(std::optional<std::chrono::nanoseconds> transact_time, std::optional<std::int64_t> security_id, std::optional<Decimal> last_px, std::optional<std::int32_t> last_qty, std::optional<std::int32_t> imbalance_qty, std::optional<SecurityTradingStatus> security_trading_status, std::optional<PotentialSecurityTradingEvent> potential_security_trading_event, const std::array<std::byte, 6>& pad6)
  : transact_time_(transact_time), security_id_(security_id), last_px_(last_px), last_qty_(last_qty), imbalance_qty_(imbalance_qty), security_trading_status_(security_trading_status), potential_security_trading_event_(potential_security_trading_event), pad6_(pad6) {}

std::optional<std::chrono::nanoseconds> AuctionClearingPrice::transact_time() const { return transact_time_; }
void AuctionClearingPrice::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::optional<std::int64_t> AuctionClearingPrice::security_id() const { return security_id_; }
void AuctionClearingPrice::set_security_id(std::optional<std::int64_t> value) { security_id_ = value; }

std::optional<Decimal> AuctionClearingPrice::last_px() const { return last_px_; }
void AuctionClearingPrice::set_last_px(std::optional<Decimal> value) { last_px_ = value; }

std::optional<std::int32_t> AuctionClearingPrice::last_qty() const { return last_qty_; }
void AuctionClearingPrice::set_last_qty(std::optional<std::int32_t> value) { last_qty_ = value; }

std::optional<std::int32_t> AuctionClearingPrice::imbalance_qty() const { return imbalance_qty_; }
void AuctionClearingPrice::set_imbalance_qty(std::optional<std::int32_t> value) { imbalance_qty_ = value; }

std::optional<SecurityTradingStatus> AuctionClearingPrice::security_trading_status() const { return security_trading_status_; }
void AuctionClearingPrice::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

std::optional<PotentialSecurityTradingEvent> AuctionClearingPrice::potential_security_trading_event() const { return potential_security_trading_event_; }
void AuctionClearingPrice::set_potential_security_trading_event(std::optional<PotentialSecurityTradingEvent> value) { potential_security_trading_event_ = value; }

const std::array<std::byte, 6>& AuctionClearingPrice::pad6() const { return pad6_; }
std::array<std::byte, 6>& AuctionClearingPrice::pad6() { return pad6_; }
void AuctionClearingPrice::set_pad6(const std::array<std::byte, 6>& value) { pad6_ = value; }

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

    last_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    imbalance_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    potential_security_trading_event_ = wire::nullable_enum<PotentialSecurityTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

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

    wire::write_i32_le(data + offset, last_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_i32_le(data + offset, imbalance_qty_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, potential_security_trading_event_ ? static_cast<std::uint8_t>(*potential_security_trading_event_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad6_.data(), 6);
    offset += 6;

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
    out << ", last_qty=";
    print::optional(out, last_qty_);
    out << ", imbalance_qty=";
    print::optional(out, imbalance_qty_);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", potential_security_trading_event=";
    print::optional(out, potential_security_trading_event_);
    out << ", pad6=";
    print::hex(out, pad6_.data(), pad6_.size());
    out << '}';
}

bool AuctionClearingPrice::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AuctionClearingPrice*>(&other);
    return that != nullptr && *this == *that;
}

bool AuctionClearingPrice::operator==(const AuctionClearingPrice& other) const {
    return transact_time_ == other.transact_time_
        && security_id_ == other.security_id_
        && last_px_ == other.last_px_
        && last_qty_ == other.last_qty_
        && imbalance_qty_ == other.imbalance_qty_
        && security_trading_status_ == other.security_trading_status_
        && potential_security_trading_event_ == other.potential_security_trading_event_
        && pad6_ == other.pad6_;
}

bool AuctionClearingPrice::operator!=(const AuctionClearingPrice& other) const {
    return !(*this == other);
}

} // namespace eurex::t7::eobi::fbe::v6_0
