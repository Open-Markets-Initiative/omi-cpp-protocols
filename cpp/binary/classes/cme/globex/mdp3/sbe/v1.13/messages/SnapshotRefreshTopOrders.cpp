#include "SnapshotRefreshTopOrders.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotRefreshTopOrders::SnapshotRefreshTopOrders(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, std::int32_t security_id, const SnapshotRefreshTopOrdersGroups& snapshot_refresh_top_orders_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), security_id_(security_id), snapshot_refresh_top_orders_groups_(snapshot_refresh_top_orders_groups) {}

std::chrono::nanoseconds SnapshotRefreshTopOrders::transact_time() const { return transact_time_; }
void SnapshotRefreshTopOrders::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& SnapshotRefreshTopOrders::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SnapshotRefreshTopOrders::match_event_indicator() { return match_event_indicator_; }
void SnapshotRefreshTopOrders::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::int32_t SnapshotRefreshTopOrders::security_id() const { return security_id_; }
void SnapshotRefreshTopOrders::set_security_id(std::int32_t value) { security_id_ = value; }

const SnapshotRefreshTopOrdersGroups& SnapshotRefreshTopOrders::snapshot_refresh_top_orders_groups() const { return snapshot_refresh_top_orders_groups_; }
SnapshotRefreshTopOrdersGroups& SnapshotRefreshTopOrders::snapshot_refresh_top_orders_groups() { return snapshot_refresh_top_orders_groups_; }
void SnapshotRefreshTopOrders::set_snapshot_refresh_top_orders_groups(const SnapshotRefreshTopOrdersGroups& value) { snapshot_refresh_top_orders_groups_ = value; }

MktdataPayloadCode SnapshotRefreshTopOrders::type() const { return message_type; }

std::string_view SnapshotRefreshTopOrders::name() const { return "Snapshot Refresh Top Orders"; }

std::size_t SnapshotRefreshTopOrders::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SnapshotRefreshTopOrders", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("SnapshotRefreshTopOrders", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    offset += snapshot_refresh_top_orders_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotRefreshTopOrders::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotRefreshTopOrders", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    offset += snapshot_refresh_top_orders_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotRefreshTopOrders::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 4 + snapshot_refresh_top_orders_groups_.encoded_size();
}

void SnapshotRefreshTopOrders::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> SnapshotRefreshTopOrders::clone() const {
    return std::make_unique<SnapshotRefreshTopOrders>(*this);
}

void SnapshotRefreshTopOrders::print(std::ostream& out) const {
    out << "SnapshotRefreshTopOrders{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", security_id=";
    out << security_id_;
    out << ", snapshot_refresh_top_orders_groups=";
    snapshot_refresh_top_orders_groups_.print(out);
    out << '}';
}

bool SnapshotRefreshTopOrders::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const SnapshotRefreshTopOrders*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotRefreshTopOrders::operator==(const SnapshotRefreshTopOrders& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && security_id_ == other.security_id_
        && snapshot_refresh_top_orders_groups_ == other.snapshot_refresh_top_orders_groups_;
}

bool SnapshotRefreshTopOrders::operator!=(const SnapshotRefreshTopOrders& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
