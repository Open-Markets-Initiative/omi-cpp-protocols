#include "MdIncrementalRefreshTradeSummary.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

MdIncrementalRefreshTradeSummary::MdIncrementalRefreshTradeSummary(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshTradeSummaryGroups& incremental_refresh_trade_summary_groups, const IncrementalRefreshTradeSummaryOrderIdGroups& incremental_refresh_trade_summary_order_id_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_trade_summary_groups_(incremental_refresh_trade_summary_groups), incremental_refresh_trade_summary_order_id_groups_(incremental_refresh_trade_summary_order_id_groups) {}

std::chrono::nanoseconds MdIncrementalRefreshTradeSummary::transact_time() const { return transact_time_; }
void MdIncrementalRefreshTradeSummary::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& MdIncrementalRefreshTradeSummary::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MdIncrementalRefreshTradeSummary::match_event_indicator() { return match_event_indicator_; }
void MdIncrementalRefreshTradeSummary::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& MdIncrementalRefreshTradeSummary::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& MdIncrementalRefreshTradeSummary::padding_2() { return padding_2_; }
void MdIncrementalRefreshTradeSummary::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshTradeSummaryGroups& MdIncrementalRefreshTradeSummary::incremental_refresh_trade_summary_groups() const { return incremental_refresh_trade_summary_groups_; }
IncrementalRefreshTradeSummaryGroups& MdIncrementalRefreshTradeSummary::incremental_refresh_trade_summary_groups() { return incremental_refresh_trade_summary_groups_; }
void MdIncrementalRefreshTradeSummary::set_incremental_refresh_trade_summary_groups(const IncrementalRefreshTradeSummaryGroups& value) { incremental_refresh_trade_summary_groups_ = value; }

const IncrementalRefreshTradeSummaryOrderIdGroups& MdIncrementalRefreshTradeSummary::incremental_refresh_trade_summary_order_id_groups() const { return incremental_refresh_trade_summary_order_id_groups_; }
IncrementalRefreshTradeSummaryOrderIdGroups& MdIncrementalRefreshTradeSummary::incremental_refresh_trade_summary_order_id_groups() { return incremental_refresh_trade_summary_order_id_groups_; }
void MdIncrementalRefreshTradeSummary::set_incremental_refresh_trade_summary_order_id_groups(const IncrementalRefreshTradeSummaryOrderIdGroups& value) { incremental_refresh_trade_summary_order_id_groups_ = value; }

MktdataPayloadCode MdIncrementalRefreshTradeSummary::type() const { return message_type; }

std::string_view MdIncrementalRefreshTradeSummary::name() const { return "Md Incremental Refresh Trade Summary"; }

std::size_t MdIncrementalRefreshTradeSummary::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MdIncrementalRefreshTradeSummary", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("MdIncrementalRefreshTradeSummary", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_trade_summary_groups_.decode(data + offset, length - offset);

    offset += incremental_refresh_trade_summary_order_id_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MdIncrementalRefreshTradeSummary::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdIncrementalRefreshTradeSummary", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_trade_summary_groups_.encode(data + offset, capacity - offset);

    offset += incremental_refresh_trade_summary_order_id_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdIncrementalRefreshTradeSummary::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_trade_summary_groups_.encoded_size() + incremental_refresh_trade_summary_order_id_groups_.encoded_size();
}

void MdIncrementalRefreshTradeSummary::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> MdIncrementalRefreshTradeSummary::clone() const {
    return std::make_unique<MdIncrementalRefreshTradeSummary>(*this);
}

void MdIncrementalRefreshTradeSummary::print(std::ostream& out) const {
    out << "MdIncrementalRefreshTradeSummary{";
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

bool MdIncrementalRefreshTradeSummary::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const MdIncrementalRefreshTradeSummary*>(&other);
    return that != nullptr && *this == *that;
}

bool MdIncrementalRefreshTradeSummary::operator==(const MdIncrementalRefreshTradeSummary& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_trade_summary_groups_ == other.incremental_refresh_trade_summary_groups_
        && incremental_refresh_trade_summary_order_id_groups_ == other.incremental_refresh_trade_summary_order_id_groups_;
}

bool MdIncrementalRefreshTradeSummary::operator!=(const MdIncrementalRefreshTradeSummary& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_5
