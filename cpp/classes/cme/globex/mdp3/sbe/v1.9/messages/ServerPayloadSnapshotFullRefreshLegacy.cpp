#include "ServerPayloadSnapshotFullRefreshLegacy.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadSnapshotFullRefreshLegacy::ServerPayloadSnapshotFullRefreshLegacy(std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::int32_t security_id, std::uint32_t rpt_seq, std::chrono::nanoseconds transact_time, std::chrono::nanoseconds last_update_time, std::optional<std::uint16_t> trade_date, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const SnapshotFullRefreshGroups& snapshot_full_refresh_groups)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), tot_num_reports_(tot_num_reports), security_id_(security_id), rpt_seq_(rpt_seq), transact_time_(transact_time), last_update_time_(last_update_time), trade_date_(trade_date), md_security_trading_status_(md_security_trading_status), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), snapshot_full_refresh_groups_(snapshot_full_refresh_groups) {}

std::uint32_t ServerPayloadSnapshotFullRefreshLegacy::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_last_msg_seq_num_processed(std::uint32_t value) { last_msg_seq_num_processed_ = value; }

std::uint32_t ServerPayloadSnapshotFullRefreshLegacy::tot_num_reports() const { return tot_num_reports_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_tot_num_reports(std::uint32_t value) { tot_num_reports_ = value; }

std::int32_t ServerPayloadSnapshotFullRefreshLegacy::security_id() const { return security_id_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t ServerPayloadSnapshotFullRefreshLegacy::rpt_seq() const { return rpt_seq_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_rpt_seq(std::uint32_t value) { rpt_seq_ = value; }

std::chrono::nanoseconds ServerPayloadSnapshotFullRefreshLegacy::transact_time() const { return transact_time_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::chrono::nanoseconds ServerPayloadSnapshotFullRefreshLegacy::last_update_time() const { return last_update_time_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<std::uint16_t> ServerPayloadSnapshotFullRefreshLegacy::trade_date() const { return trade_date_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_trade_date(std::optional<std::uint16_t> value) { trade_date_ = value; }

std::optional<MdSecurityTradingStatus> ServerPayloadSnapshotFullRefreshLegacy::md_security_trading_status() const { return md_security_trading_status_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshLegacy::high_limit_price() const { return high_limit_price_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshLegacy::low_limit_price() const { return low_limit_price_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> ServerPayloadSnapshotFullRefreshLegacy::max_price_variation() const { return max_price_variation_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

const SnapshotFullRefreshGroups& ServerPayloadSnapshotFullRefreshLegacy::snapshot_full_refresh_groups() const { return snapshot_full_refresh_groups_; }
SnapshotFullRefreshGroups& ServerPayloadSnapshotFullRefreshLegacy::snapshot_full_refresh_groups() { return snapshot_full_refresh_groups_; }
void ServerPayloadSnapshotFullRefreshLegacy::set_snapshot_full_refresh_groups(const SnapshotFullRefreshGroups& value) { snapshot_full_refresh_groups_ = value; }

ServerTcpMessageCode ServerPayloadSnapshotFullRefreshLegacy::type() const { return message_type; }

std::string_view ServerPayloadSnapshotFullRefreshLegacy::name() const { return "Snapshot Full Refresh Legacy"; }

std::size_t ServerPayloadSnapshotFullRefreshLegacy::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 4, length);
    last_msg_seq_num_processed_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 4, length);
    tot_num_reports_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 4, length);
    rpt_seq_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 2, length);
    trade_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadSnapshotFullRefreshLegacy", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    offset += snapshot_full_refresh_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadSnapshotFullRefreshLegacy::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadSnapshotFullRefreshLegacy", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_msg_seq_num_processed_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_num_reports_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(rpt_seq_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(last_update_time_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, trade_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u8(data + offset, md_security_trading_status_ ? static_cast<std::uint8_t>(*md_security_trading_status_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    offset += snapshot_full_refresh_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadSnapshotFullRefreshLegacy::encoded_size() const {
    return 4 + 4 + 4 + 4 + 8 + 8 + 2 + 1 + 8 + 8 + 8 + snapshot_full_refresh_groups_.encoded_size();
}

void ServerPayloadSnapshotFullRefreshLegacy::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadSnapshotFullRefreshLegacy::clone() const {
    return std::make_unique<ServerPayloadSnapshotFullRefreshLegacy>(*this);
}

void ServerPayloadSnapshotFullRefreshLegacy::print(std::ostream& out) const {
    out << "ServerPayloadSnapshotFullRefreshLegacy{";
    out << "last_msg_seq_num_processed=";
    out << last_msg_seq_num_processed_;
    out << ", tot_num_reports=";
    out << tot_num_reports_;
    out << ", security_id=";
    out << security_id_;
    out << ", rpt_seq=";
    out << rpt_seq_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", last_update_time=";
    out << last_update_time_.count();
    out << ", trade_date=";
    print::optional(out, trade_date_);
    out << ", md_security_trading_status=";
    print::optional(out, md_security_trading_status_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", snapshot_full_refresh_groups=";
    snapshot_full_refresh_groups_.print(out);
    out << '}';
}

bool ServerPayloadSnapshotFullRefreshLegacy::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadSnapshotFullRefreshLegacy*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadSnapshotFullRefreshLegacy::operator==(const ServerPayloadSnapshotFullRefreshLegacy& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && tot_num_reports_ == other.tot_num_reports_
        && security_id_ == other.security_id_
        && rpt_seq_ == other.rpt_seq_
        && transact_time_ == other.transact_time_
        && last_update_time_ == other.last_update_time_
        && trade_date_ == other.trade_date_
        && md_security_trading_status_ == other.md_security_trading_status_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && snapshot_full_refresh_groups_ == other.snapshot_full_refresh_groups_;
}

bool ServerPayloadSnapshotFullRefreshLegacy::operator!=(const ServerPayloadSnapshotFullRefreshLegacy& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
