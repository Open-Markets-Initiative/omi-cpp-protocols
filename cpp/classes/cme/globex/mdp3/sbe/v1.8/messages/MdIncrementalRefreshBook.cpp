#include "MdIncrementalRefreshBook.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

MdIncrementalRefreshBook::MdIncrementalRefreshBook(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 2>& padding_2, const IncrementalRefreshBookGroups& incremental_refresh_book_groups, const IncrementalRefreshBookOrderIdGroups& incremental_refresh_book_order_id_groups)
  : transact_time_(transact_time), match_event_indicator_(match_event_indicator), padding_2_(padding_2), incremental_refresh_book_groups_(incremental_refresh_book_groups), incremental_refresh_book_order_id_groups_(incremental_refresh_book_order_id_groups) {}

std::chrono::nanoseconds MdIncrementalRefreshBook::transact_time() const { return transact_time_; }
void MdIncrementalRefreshBook::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const MatchEventIndicator& MdIncrementalRefreshBook::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MdIncrementalRefreshBook::match_event_indicator() { return match_event_indicator_; }
void MdIncrementalRefreshBook::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 2>& MdIncrementalRefreshBook::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& MdIncrementalRefreshBook::padding_2() { return padding_2_; }
void MdIncrementalRefreshBook::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

const IncrementalRefreshBookGroups& MdIncrementalRefreshBook::incremental_refresh_book_groups() const { return incremental_refresh_book_groups_; }
IncrementalRefreshBookGroups& MdIncrementalRefreshBook::incremental_refresh_book_groups() { return incremental_refresh_book_groups_; }
void MdIncrementalRefreshBook::set_incremental_refresh_book_groups(const IncrementalRefreshBookGroups& value) { incremental_refresh_book_groups_ = value; }

const IncrementalRefreshBookOrderIdGroups& MdIncrementalRefreshBook::incremental_refresh_book_order_id_groups() const { return incremental_refresh_book_order_id_groups_; }
IncrementalRefreshBookOrderIdGroups& MdIncrementalRefreshBook::incremental_refresh_book_order_id_groups() { return incremental_refresh_book_order_id_groups_; }
void MdIncrementalRefreshBook::set_incremental_refresh_book_order_id_groups(const IncrementalRefreshBookOrderIdGroups& value) { incremental_refresh_book_order_id_groups_ = value; }

MktdataPayloadCode MdIncrementalRefreshBook::type() const { return message_type; }

std::string_view MdIncrementalRefreshBook::name() const { return "Md Incremental Refresh Book"; }

std::size_t MdIncrementalRefreshBook::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("MdIncrementalRefreshBook", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("MdIncrementalRefreshBook", offset + 2, length);
    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_book_groups_.decode(data + offset, length - offset);

    offset += incremental_refresh_book_order_id_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MdIncrementalRefreshBook::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdIncrementalRefreshBook", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    offset += incremental_refresh_book_groups_.encode(data + offset, capacity - offset);

    offset += incremental_refresh_book_order_id_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdIncrementalRefreshBook::encoded_size() const {
    return 8 + match_event_indicator_.encoded_size() + 2 + incremental_refresh_book_groups_.encoded_size() + incremental_refresh_book_order_id_groups_.encoded_size();
}

void MdIncrementalRefreshBook::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> MdIncrementalRefreshBook::clone() const {
    return std::make_unique<MdIncrementalRefreshBook>(*this);
}

void MdIncrementalRefreshBook::print(std::ostream& out) const {
    out << "MdIncrementalRefreshBook{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << ", incremental_refresh_book_groups=";
    incremental_refresh_book_groups_.print(out);
    out << ", incremental_refresh_book_order_id_groups=";
    incremental_refresh_book_order_id_groups_.print(out);
    out << '}';
}

bool MdIncrementalRefreshBook::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const MdIncrementalRefreshBook*>(&other);
    return that != nullptr && *this == *that;
}

bool MdIncrementalRefreshBook::operator==(const MdIncrementalRefreshBook& other) const {
    return transact_time_ == other.transact_time_
        && match_event_indicator_ == other.match_event_indicator_
        && padding_2_ == other.padding_2_
        && incremental_refresh_book_groups_ == other.incremental_refresh_book_groups_
        && incremental_refresh_book_order_id_groups_ == other.incremental_refresh_book_order_id_groups_;
}

bool MdIncrementalRefreshBook::operator!=(const MdIncrementalRefreshBook& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
