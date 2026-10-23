#include "SnapshotFullRefreshTcpLongQty.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotFullRefreshTcpLongQty::SnapshotFullRefreshTcpLongQty(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, std::int32_t security_id, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const SnapshotfullRefreshTcpLongGroups& snapshotfull_refresh_tcp_long_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), security_id_(security_id), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), snapshotfull_refresh_tcp_long_groups_(snapshotfull_refresh_tcp_long_groups) {}

std::chrono::nanoseconds SnapshotFullRefreshTcpLongQty::transact_time() const { return transact_time_; }
void SnapshotFullRefreshTcpLongQty::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& SnapshotFullRefreshTcpLongQty::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SnapshotFullRefreshTcpLongQty::match_event_indicator() { return match_event_indicator_; }
void SnapshotFullRefreshTcpLongQty::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::int32_t SnapshotFullRefreshTcpLongQty::security_id() const { return security_id_; }
void SnapshotFullRefreshTcpLongQty::set_security_id(std::int32_t value) { security_id_ = value; }

std::optional<Decimal> SnapshotFullRefreshTcpLongQty::high_limit_price() const { return high_limit_price_; }
void SnapshotFullRefreshTcpLongQty::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> SnapshotFullRefreshTcpLongQty::low_limit_price() const { return low_limit_price_; }
void SnapshotFullRefreshTcpLongQty::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> SnapshotFullRefreshTcpLongQty::max_price_variation() const { return max_price_variation_; }
void SnapshotFullRefreshTcpLongQty::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

const SnapshotfullRefreshTcpLongGroups& SnapshotFullRefreshTcpLongQty::snapshotfull_refresh_tcp_long_groups() const { return snapshotfull_refresh_tcp_long_groups_; }
SnapshotfullRefreshTcpLongGroups& SnapshotFullRefreshTcpLongQty::snapshotfull_refresh_tcp_long_groups() { return snapshotfull_refresh_tcp_long_groups_; }
void SnapshotFullRefreshTcpLongQty::set_snapshotfull_refresh_tcp_long_groups(const SnapshotfullRefreshTcpLongGroups& value) { snapshotfull_refresh_tcp_long_groups_ = value; }

MktdataPayloadCode SnapshotFullRefreshTcpLongQty::type() const { return message_type; }

std::string_view SnapshotFullRefreshTcpLongQty::name() const { return "Snapshot Full Refresh Tcp Long Qty"; }

std::size_t SnapshotFullRefreshTcpLongQty::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SnapshotFullRefreshTcpLongQty", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("SnapshotFullRefreshTcpLongQty", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshTcpLongQty", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("SnapshotFullRefreshTcpLongQty", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("SnapshotFullRefreshTcpLongQty", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    offset += snapshotfull_refresh_tcp_long_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotFullRefreshTcpLongQty::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshTcpLongQty", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    offset += snapshotfull_refresh_tcp_long_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotFullRefreshTcpLongQty::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 4 + 8 + 8 + 8 + snapshotfull_refresh_tcp_long_groups_.encoded_size();
}

void SnapshotFullRefreshTcpLongQty::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> SnapshotFullRefreshTcpLongQty::clone() const {
    return std::make_unique<SnapshotFullRefreshTcpLongQty>(*this);
}

void SnapshotFullRefreshTcpLongQty::print(std::ostream& out) const {
    out << "SnapshotFullRefreshTcpLongQty{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", snapshotfull_refresh_tcp_long_groups=";
    snapshotfull_refresh_tcp_long_groups_.print(out);
    out << '}';
}

bool SnapshotFullRefreshTcpLongQty::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const SnapshotFullRefreshTcpLongQty*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotFullRefreshTcpLongQty::operator==(const SnapshotFullRefreshTcpLongQty& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && security_id_ == other.security_id_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && snapshotfull_refresh_tcp_long_groups_ == other.snapshotfull_refresh_tcp_long_groups_;
}

bool SnapshotFullRefreshTcpLongQty::operator!=(const SnapshotFullRefreshTcpLongQty& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
