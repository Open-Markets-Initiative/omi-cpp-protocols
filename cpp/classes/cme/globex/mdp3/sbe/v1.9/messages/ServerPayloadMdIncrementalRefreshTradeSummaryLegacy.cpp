#include "ServerPayloadMdIncrementalRefreshTradeSummaryLegacy.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::ServerPayloadMdIncrementalRefreshTradeSummaryLegacy(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshTradeSummaryGroups& incremental_refresh_trade_summary_groups, const IncrementalRefreshTradeSummaryOrderIdGroups& incremental_refresh_trade_summary_order_id_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_trade_summary_groups_(incremental_refresh_trade_summary_groups), incremental_refresh_trade_summary_order_id_groups_(incremental_refresh_trade_summary_order_id_groups) {}

std::chrono::nanoseconds ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::transact_time() const { return transact_time_; }
void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::padding_2() { return padding_2_; }
void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshTradeSummaryGroups& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::incremental_refresh_trade_summary_groups() const { return incremental_refresh_trade_summary_groups_; }
IncrementalRefreshTradeSummaryGroups& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::incremental_refresh_trade_summary_groups() { return incremental_refresh_trade_summary_groups_; }
void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::set_incremental_refresh_trade_summary_groups(const IncrementalRefreshTradeSummaryGroups& value) { incremental_refresh_trade_summary_groups_ = value; }

const IncrementalRefreshTradeSummaryOrderIdGroups& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::incremental_refresh_trade_summary_order_id_groups() const { return incremental_refresh_trade_summary_order_id_groups_; }
IncrementalRefreshTradeSummaryOrderIdGroups& ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::incremental_refresh_trade_summary_order_id_groups() { return incremental_refresh_trade_summary_order_id_groups_; }
void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::set_incremental_refresh_trade_summary_order_id_groups(const IncrementalRefreshTradeSummaryOrderIdGroups& value) { incremental_refresh_trade_summary_order_id_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::type() const { return message_type; }

std::string_view ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::name() const { return "Md Incremental Refresh Trade Summary Legacy"; }

std::size_t ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadMdIncrementalRefreshTradeSummaryLegacy", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdIncrementalRefreshTradeSummaryLegacy", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_trade_summary_groups_.decode(data + offset, length - offset);

    offset += incremental_refresh_trade_summary_order_id_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdIncrementalRefreshTradeSummaryLegacy", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_trade_summary_groups_.encode(data + offset, capacity - offset);

    offset += incremental_refresh_trade_summary_order_id_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_trade_summary_groups_.encoded_size() + incremental_refresh_trade_summary_order_id_groups_.encoded_size();
}

void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::clone() const {
    return std::make_unique<ServerPayloadMdIncrementalRefreshTradeSummaryLegacy>(*this);
}

void ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::print(std::ostream& out) const {
    out << "ServerPayloadMdIncrementalRefreshTradeSummaryLegacy{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", incremental_refresh_trade_summary_groups=";
    incremental_refresh_trade_summary_groups_.print(out);
    out << ", incremental_refresh_trade_summary_order_id_groups=";
    incremental_refresh_trade_summary_order_id_groups_.print(out);
    out << '}';
}

bool ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdIncrementalRefreshTradeSummaryLegacy*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::operator==(const ServerPayloadMdIncrementalRefreshTradeSummaryLegacy& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_trade_summary_groups_ == other.incremental_refresh_trade_summary_groups_
        && incremental_refresh_trade_summary_order_id_groups_ == other.incremental_refresh_trade_summary_order_id_groups_;
}

bool ServerPayloadMdIncrementalRefreshTradeSummaryLegacy::operator!=(const ServerPayloadMdIncrementalRefreshTradeSummaryLegacy& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
