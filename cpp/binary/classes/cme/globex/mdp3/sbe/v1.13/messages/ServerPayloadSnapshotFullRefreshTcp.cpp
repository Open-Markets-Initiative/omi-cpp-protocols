#include "ServerPayloadSnapshotFullRefreshTcp.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadSnapshotFullRefreshTcp::ServerPayloadSnapshotFullRefreshTcp(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, std::int32_t security_id, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const SnapshotFullRefreshTcpGroups& snapshot_full_refresh_tcp_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), security_id_(security_id), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), snapshot_full_refresh_tcp_groups_(snapshot_full_refresh_tcp_groups) {}

std::chrono::nanoseconds ServerPayloadSnapshotFullRefreshTcp::transact_time() const { return transact_time_; }
void ServerPayloadSnapshotFullRefreshTcp::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ServerPayloadSnapshotFullRefreshTcp::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadSnapshotFullRefreshTcp::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadSnapshotFullRefreshTcp::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::int32_t ServerPayloadSnapshotFullRefreshTcp::security_id() const { return security_id_; }
void ServerPayloadSnapshotFullRefreshTcp::set_security_id(std::int32_t value) { security_id_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshTcp::high_limit_price() const { return high_limit_price_; }
void ServerPayloadSnapshotFullRefreshTcp::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshTcp::low_limit_price() const { return low_limit_price_; }
void ServerPayloadSnapshotFullRefreshTcp::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshTcp::max_price_variation() const { return max_price_variation_; }
void ServerPayloadSnapshotFullRefreshTcp::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

const SnapshotFullRefreshTcpGroups& ServerPayloadSnapshotFullRefreshTcp::snapshot_full_refresh_tcp_groups() const { return snapshot_full_refresh_tcp_groups_; }
SnapshotFullRefreshTcpGroups& ServerPayloadSnapshotFullRefreshTcp::snapshot_full_refresh_tcp_groups() { return snapshot_full_refresh_tcp_groups_; }
void ServerPayloadSnapshotFullRefreshTcp::set_snapshot_full_refresh_tcp_groups(const SnapshotFullRefreshTcpGroups& value) { snapshot_full_refresh_tcp_groups_ = value; }

ServerTcpMessageCode ServerPayloadSnapshotFullRefreshTcp::type() const { return message_type; }

std::string_view ServerPayloadSnapshotFullRefreshTcp::name() const { return "Snapshot Full Refresh Tcp"; }

std::size_t ServerPayloadSnapshotFullRefreshTcp::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadSnapshotFullRefreshTcp", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadSnapshotFullRefreshTcp", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSnapshotFullRefreshTcp", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshTcp", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshTcp", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    offset += snapshot_full_refresh_tcp_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadSnapshotFullRefreshTcp::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadSnapshotFullRefreshTcp", encoded_size(), capacity);

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

    offset += snapshot_full_refresh_tcp_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadSnapshotFullRefreshTcp::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 4 + 8 + 8 + 8 + snapshot_full_refresh_tcp_groups_.encoded_size();
}

void ServerPayloadSnapshotFullRefreshTcp::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadSnapshotFullRefreshTcp::clone() const {
    return std::make_unique<ServerPayloadSnapshotFullRefreshTcp>(*this);
}

void ServerPayloadSnapshotFullRefreshTcp::print(std::ostream& out) const {
    out << "ServerPayloadSnapshotFullRefreshTcp{";
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
    out << ", snapshot_full_refresh_tcp_groups=";
    snapshot_full_refresh_tcp_groups_.print(out);
    out << '}';
}

bool ServerPayloadSnapshotFullRefreshTcp::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadSnapshotFullRefreshTcp*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadSnapshotFullRefreshTcp::operator==(const ServerPayloadSnapshotFullRefreshTcp& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && security_id_ == other.security_id_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && snapshot_full_refresh_tcp_groups_ == other.snapshot_full_refresh_tcp_groups_;
}

bool ServerPayloadSnapshotFullRefreshTcp::operator!=(const ServerPayloadSnapshotFullRefreshTcp& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
