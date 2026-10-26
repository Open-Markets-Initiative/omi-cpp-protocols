#include "MdIncrementalRefreshBookLongQty.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MdIncrementalRefreshBookLongQty::MdIncrementalRefreshBookLongQty(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshBookLongGroups& incremental_refresh_book_long_groups, const IncrementalRefreshBookLongOrderIdGroups& incremental_refresh_book_long_order_id_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_book_long_groups_(incremental_refresh_book_long_groups), incremental_refresh_book_long_order_id_groups_(incremental_refresh_book_long_order_id_groups) {}

std::chrono::nanoseconds MdIncrementalRefreshBookLongQty::transact_time() const { return transact_time_; }
void MdIncrementalRefreshBookLongQty::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& MdIncrementalRefreshBookLongQty::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MdIncrementalRefreshBookLongQty::match_event_indicator() { return match_event_indicator_; }
void MdIncrementalRefreshBookLongQty::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& MdIncrementalRefreshBookLongQty::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& MdIncrementalRefreshBookLongQty::padding_2() { return padding_2_; }
void MdIncrementalRefreshBookLongQty::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshBookLongGroups& MdIncrementalRefreshBookLongQty::incremental_refresh_book_long_groups() const { return incremental_refresh_book_long_groups_; }
IncrementalRefreshBookLongGroups& MdIncrementalRefreshBookLongQty::incremental_refresh_book_long_groups() { return incremental_refresh_book_long_groups_; }
void MdIncrementalRefreshBookLongQty::set_incremental_refresh_book_long_groups(const IncrementalRefreshBookLongGroups& value) { incremental_refresh_book_long_groups_ = value; }

const IncrementalRefreshBookLongOrderIdGroups& MdIncrementalRefreshBookLongQty::incremental_refresh_book_long_order_id_groups() const { return incremental_refresh_book_long_order_id_groups_; }
IncrementalRefreshBookLongOrderIdGroups& MdIncrementalRefreshBookLongQty::incremental_refresh_book_long_order_id_groups() { return incremental_refresh_book_long_order_id_groups_; }
void MdIncrementalRefreshBookLongQty::set_incremental_refresh_book_long_order_id_groups(const IncrementalRefreshBookLongOrderIdGroups& value) { incremental_refresh_book_long_order_id_groups_ = value; }

MktdataPayloadCode MdIncrementalRefreshBookLongQty::type() const { return message_type; }

std::string_view MdIncrementalRefreshBookLongQty::name() const { return "Md Incremental Refresh Book Long Qty"; }

std::size_t MdIncrementalRefreshBookLongQty::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MdIncrementalRefreshBookLongQty", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("MdIncrementalRefreshBookLongQty", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_book_long_groups_.decode(data + offset, length - offset);

    offset += incremental_refresh_book_long_order_id_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MdIncrementalRefreshBookLongQty::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdIncrementalRefreshBookLongQty", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_book_long_groups_.encode(data + offset, capacity - offset);

    offset += incremental_refresh_book_long_order_id_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdIncrementalRefreshBookLongQty::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_book_long_groups_.encoded_size() + incremental_refresh_book_long_order_id_groups_.encoded_size();
}

void MdIncrementalRefreshBookLongQty::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> MdIncrementalRefreshBookLongQty::clone() const {
    return std::make_unique<MdIncrementalRefreshBookLongQty>(*this);
}

void MdIncrementalRefreshBookLongQty::print(std::ostream& out) const {
    out << "MdIncrementalRefreshBookLongQty{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", incremental_refresh_book_long_groups=";
    incremental_refresh_book_long_groups_.print(out);
    out << ", incremental_refresh_book_long_order_id_groups=";
    incremental_refresh_book_long_order_id_groups_.print(out);
    out << '}';
}

bool MdIncrementalRefreshBookLongQty::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const MdIncrementalRefreshBookLongQty*>(&other);
    return that != nullptr && *this == *that;
}

bool MdIncrementalRefreshBookLongQty::operator==(const MdIncrementalRefreshBookLongQty& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_book_long_groups_ == other.incremental_refresh_book_long_groups_
        && incremental_refresh_book_long_order_id_groups_ == other.incremental_refresh_book_long_order_id_groups_;
}

bool MdIncrementalRefreshBookLongQty::operator!=(const MdIncrementalRefreshBookLongQty& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
