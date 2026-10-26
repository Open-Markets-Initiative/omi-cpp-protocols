#include "SnapshotFullRefreshOrderBook.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SnapshotFullRefreshOrderBook::SnapshotFullRefreshOrderBook(std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::int32_t security_id, std::uint32_t no_chunks, std::uint32_t current_chunk, std::chrono::nanoseconds transact_time, const SnapshotFullRefreshOrderBookGroups& snapshot_full_refresh_order_book_groups)
  : last_msg_seq_num_processed_(last_msg_seq_num_processed), tot_num_reports_(tot_num_reports), security_id_(security_id), no_chunks_(no_chunks), current_chunk_(current_chunk), transact_time_(transact_time), snapshot_full_refresh_order_book_groups_(snapshot_full_refresh_order_book_groups) {}

std::uint32_t SnapshotFullRefreshOrderBook::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void SnapshotFullRefreshOrderBook::set_last_msg_seq_num_processed(std::uint32_t value) { last_msg_seq_num_processed_ = value; }

std::uint32_t SnapshotFullRefreshOrderBook::tot_num_reports() const { return tot_num_reports_; }
void SnapshotFullRefreshOrderBook::set_tot_num_reports(std::uint32_t value) { tot_num_reports_ = value; }

std::int32_t SnapshotFullRefreshOrderBook::security_id() const { return security_id_; }
void SnapshotFullRefreshOrderBook::set_security_id(std::int32_t value) { security_id_ = value; }

std::uint32_t SnapshotFullRefreshOrderBook::no_chunks() const { return no_chunks_; }
void SnapshotFullRefreshOrderBook::set_no_chunks(std::uint32_t value) { no_chunks_ = value; }

std::uint32_t SnapshotFullRefreshOrderBook::current_chunk() const { return current_chunk_; }
void SnapshotFullRefreshOrderBook::set_current_chunk(std::uint32_t value) { current_chunk_ = value; }

std::chrono::nanoseconds SnapshotFullRefreshOrderBook::transact_time() const { return transact_time_; }
void SnapshotFullRefreshOrderBook::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const SnapshotFullRefreshOrderBookGroups& SnapshotFullRefreshOrderBook::snapshot_full_refresh_order_book_groups() const { return snapshot_full_refresh_order_book_groups_; }
SnapshotFullRefreshOrderBookGroups& SnapshotFullRefreshOrderBook::snapshot_full_refresh_order_book_groups() { return snapshot_full_refresh_order_book_groups_; }
void SnapshotFullRefreshOrderBook::set_snapshot_full_refresh_order_book_groups(const SnapshotFullRefreshOrderBookGroups& value) { snapshot_full_refresh_order_book_groups_ = value; }

MktdataPayloadCode SnapshotFullRefreshOrderBook::type() const { return message_type; }

std::string_view SnapshotFullRefreshOrderBook::name() const { return "Snapshot Full Refresh Order Book"; }

std::size_t SnapshotFullRefreshOrderBook::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SnapshotFullRefreshOrderBook", offset + 4, length);
    last_msg_seq_num_processed_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshOrderBook", offset + 4, length);
    tot_num_reports_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshOrderBook", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshOrderBook", offset + 4, length);
    no_chunks_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshOrderBook", offset + 4, length);
    current_chunk_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SnapshotFullRefreshOrderBook", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    offset += snapshot_full_refresh_order_book_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrderBook::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrderBook", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_msg_seq_num_processed_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_num_reports_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(no_chunks_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(current_chunk_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    offset += snapshot_full_refresh_order_book_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrderBook::encoded_size() const {
    return 4 + 4 + 4 + 4 + 4 + 8 + snapshot_full_refresh_order_book_groups_.encoded_size();
}

void SnapshotFullRefreshOrderBook::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> SnapshotFullRefreshOrderBook::clone() const {
    return std::make_unique<SnapshotFullRefreshOrderBook>(*this);
}

void SnapshotFullRefreshOrderBook::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrderBook{";
    out << "last_msg_seq_num_processed=";
    out << last_msg_seq_num_processed_;
    out << ", tot_num_reports=";
    out << tot_num_reports_;
    out << ", security_id=";
    out << security_id_;
    out << ", no_chunks=";
    out << no_chunks_;
    out << ", current_chunk=";
    out << current_chunk_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", snapshot_full_refresh_order_book_groups=";
    snapshot_full_refresh_order_book_groups_.print(out);
    out << '}';
}

bool SnapshotFullRefreshOrderBook::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const SnapshotFullRefreshOrderBook*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotFullRefreshOrderBook::operator==(const SnapshotFullRefreshOrderBook& other) const {
    return last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && tot_num_reports_ == other.tot_num_reports_
        && security_id_ == other.security_id_
        && no_chunks_ == other.no_chunks_
        && current_chunk_ == other.current_chunk_
        && transact_time_ == other.transact_time_
        && snapshot_full_refresh_order_book_groups_ == other.snapshot_full_refresh_order_book_groups_;
}

bool SnapshotFullRefreshOrderBook::operator!=(const SnapshotFullRefreshOrderBook& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
