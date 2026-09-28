#include "SnapshotFullRefreshHeader30Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

SnapshotFullRefreshHeader30Message::SnapshotFullRefreshHeader30Message(std::uint64_t security_id, std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::uint32_t tot_num_bids, std::uint32_t tot_num_offers, std::uint16_t tot_num_stats, const std::array<std::byte, 2>& offset_26_padding_2, std::optional<std::uint32_t> last_rpt_seq)
  : security_id_(security_id), last_msg_seq_num_processed_(last_msg_seq_num_processed), tot_num_reports_(tot_num_reports), tot_num_bids_(tot_num_bids), tot_num_offers_(tot_num_offers), tot_num_stats_(tot_num_stats), offset_26_padding_2_(offset_26_padding_2), last_rpt_seq_(last_rpt_seq) {}

std::uint64_t SnapshotFullRefreshHeader30Message::security_id() const { return security_id_; }
void SnapshotFullRefreshHeader30Message::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint32_t SnapshotFullRefreshHeader30Message::last_msg_seq_num_processed() const { return last_msg_seq_num_processed_; }
void SnapshotFullRefreshHeader30Message::set_last_msg_seq_num_processed(std::uint32_t value) { last_msg_seq_num_processed_ = value; }

std::uint32_t SnapshotFullRefreshHeader30Message::tot_num_reports() const { return tot_num_reports_; }
void SnapshotFullRefreshHeader30Message::set_tot_num_reports(std::uint32_t value) { tot_num_reports_ = value; }

std::uint32_t SnapshotFullRefreshHeader30Message::tot_num_bids() const { return tot_num_bids_; }
void SnapshotFullRefreshHeader30Message::set_tot_num_bids(std::uint32_t value) { tot_num_bids_ = value; }

std::uint32_t SnapshotFullRefreshHeader30Message::tot_num_offers() const { return tot_num_offers_; }
void SnapshotFullRefreshHeader30Message::set_tot_num_offers(std::uint32_t value) { tot_num_offers_ = value; }

std::uint16_t SnapshotFullRefreshHeader30Message::tot_num_stats() const { return tot_num_stats_; }
void SnapshotFullRefreshHeader30Message::set_tot_num_stats(std::uint16_t value) { tot_num_stats_ = value; }

const std::array<std::byte, 2>& SnapshotFullRefreshHeader30Message::offset_26_padding_2() const { return offset_26_padding_2_; }
std::array<std::byte, 2>& SnapshotFullRefreshHeader30Message::offset_26_padding_2() { return offset_26_padding_2_; }
void SnapshotFullRefreshHeader30Message::set_offset_26_padding_2(const std::array<std::byte, 2>& value) { offset_26_padding_2_ = value; }

std::optional<std::uint32_t> SnapshotFullRefreshHeader30Message::last_rpt_seq() const { return last_rpt_seq_; }
void SnapshotFullRefreshHeader30Message::set_last_rpt_seq(std::optional<std::uint32_t> value) { last_rpt_seq_ = value; }

MessageCode SnapshotFullRefreshHeader30Message::type() const { return message_type; }

std::string_view SnapshotFullRefreshHeader30Message::name() const { return "Snapshot Full Refresh Header 30 Message"; }

std::size_t SnapshotFullRefreshHeader30Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SnapshotFullRefreshHeader30Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    last_msg_seq_num_processed_ = wire::read_u32_le(data + offset);
    offset += 4;

    tot_num_reports_ = wire::read_u32_le(data + offset);
    offset += 4;

    tot_num_bids_ = wire::read_u32_le(data + offset);
    offset += 4;

    tot_num_offers_ = wire::read_u32_le(data + offset);
    offset += 4;

    tot_num_stats_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, offset_26_padding_2_.data(), 2);
    offset += 2;

    last_rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t SnapshotFullRefreshHeader30Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshHeader30Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(last_msg_seq_num_processed_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_num_reports_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_num_bids_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_num_offers_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(tot_num_stats_));
    offset += 2;

    wire::write_bytes(data + offset, offset_26_padding_2_.data(), 2);
    offset += 2;

    wire::write_u32_le(data + offset, last_rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t SnapshotFullRefreshHeader30Message::encoded_size() const {
    return wire_size;
}

void SnapshotFullRefreshHeader30Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotFullRefreshHeader30Message::clone() const {
    return std::make_unique<SnapshotFullRefreshHeader30Message>(*this);
}

void SnapshotFullRefreshHeader30Message::print(std::ostream& out) const {
    out << "SnapshotFullRefreshHeader30Message{";
    out << "security_id=";
    out << security_id_;
    out << ", last_msg_seq_num_processed=";
    out << last_msg_seq_num_processed_;
    out << ", tot_num_reports=";
    out << tot_num_reports_;
    out << ", tot_num_bids=";
    out << tot_num_bids_;
    out << ", tot_num_offers=";
    out << tot_num_offers_;
    out << ", tot_num_stats=";
    out << tot_num_stats_;
    out << ", offset_26_padding_2=";
    print::hex(out, offset_26_padding_2_.data(), offset_26_padding_2_.size());
    out << ", last_rpt_seq=";
    print::optional(out, last_rpt_seq_);
    out << '}';
}

bool SnapshotFullRefreshHeader30Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotFullRefreshHeader30Message*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotFullRefreshHeader30Message::operator==(const SnapshotFullRefreshHeader30Message& other) const {
    return security_id_ == other.security_id_
        && last_msg_seq_num_processed_ == other.last_msg_seq_num_processed_
        && tot_num_reports_ == other.tot_num_reports_
        && tot_num_bids_ == other.tot_num_bids_
        && tot_num_offers_ == other.tot_num_offers_
        && tot_num_stats_ == other.tot_num_stats_
        && offset_26_padding_2_ == other.offset_26_padding_2_
        && last_rpt_seq_ == other.last_rpt_seq_;
}

bool SnapshotFullRefreshHeader30Message::operator!=(const SnapshotFullRefreshHeader30Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
