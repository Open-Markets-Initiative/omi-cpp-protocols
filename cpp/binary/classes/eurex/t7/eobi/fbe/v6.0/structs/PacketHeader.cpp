#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

PacketHeader::PacketHeader(const EobiHeader& eobi_header, std::uint32_t appl_seq_num, std::optional<std::int32_t> market_segment_id, std::optional<std::uint8_t> partition_id, std::optional<CompletionIndicator> completion_indicator, std::optional<ApplSeqResetIndicator> appl_seq_reset_indicator, const std::array<std::byte, 5>& pad5, std::optional<std::chrono::nanoseconds> transact_time)
  : eobi_header_(eobi_header), appl_seq_num_(appl_seq_num), market_segment_id_(market_segment_id), partition_id_(partition_id), completion_indicator_(completion_indicator), appl_seq_reset_indicator_(appl_seq_reset_indicator), pad5_(pad5), transact_time_(transact_time) {}

const EobiHeader& PacketHeader::eobi_header() const { return eobi_header_; }
EobiHeader& PacketHeader::eobi_header() { return eobi_header_; }
void PacketHeader::set_eobi_header(const EobiHeader& value) { eobi_header_ = value; }

std::uint32_t PacketHeader::appl_seq_num() const { return appl_seq_num_; }
void PacketHeader::set_appl_seq_num(std::uint32_t value) { appl_seq_num_ = value; }

std::optional<std::int32_t> PacketHeader::market_segment_id() const { return market_segment_id_; }
void PacketHeader::set_market_segment_id(std::optional<std::int32_t> value) { market_segment_id_ = value; }

std::optional<std::uint8_t> PacketHeader::partition_id() const { return partition_id_; }
void PacketHeader::set_partition_id(std::optional<std::uint8_t> value) { partition_id_ = value; }

std::optional<CompletionIndicator> PacketHeader::completion_indicator() const { return completion_indicator_; }
void PacketHeader::set_completion_indicator(std::optional<CompletionIndicator> value) { completion_indicator_ = value; }

std::optional<ApplSeqResetIndicator> PacketHeader::appl_seq_reset_indicator() const { return appl_seq_reset_indicator_; }
void PacketHeader::set_appl_seq_reset_indicator(std::optional<ApplSeqResetIndicator> value) { appl_seq_reset_indicator_ = value; }

const std::array<std::byte, 5>& PacketHeader::pad5() const { return pad5_; }
std::array<std::byte, 5>& PacketHeader::pad5() { return pad5_; }
void PacketHeader::set_pad5(const std::array<std::byte, 5>& value) { pad5_ = value; }

std::optional<std::chrono::nanoseconds> PacketHeader::transact_time() const { return transact_time_; }
void PacketHeader::set_transact_time(std::optional<std::chrono::nanoseconds> value) { transact_time_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    offset += eobi_header_.decode(data + offset, length - offset);

    appl_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_segment_id_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0x80000000LL));
    offset += 4;

    partition_id_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    completion_indicator_ = wire::nullable_enum<CompletionIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    appl_seq_reset_indicator_ = wire::nullable_enum<ApplSeqResetIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::read_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    transact_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    offset += eobi_header_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(appl_seq_num_));
    offset += 4;

    wire::write_i32_le(data + offset, market_segment_id_.value_or(static_cast<std::int32_t>(0x80000000LL)));
    offset += 4;

    wire::write_u8(data + offset, partition_id_.value_or(static_cast<std::uint8_t>(0xFFULL)));
    offset += 1;

    wire::write_u8(data + offset, completion_indicator_ ? static_cast<std::uint8_t>(*completion_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_u8(data + offset, appl_seq_reset_indicator_ ? static_cast<std::uint8_t>(*appl_seq_reset_indicator_) : static_cast<std::uint8_t>(0xFFULL));
    offset += 1;

    wire::write_bytes(data + offset, pad5_.data(), 5);
    offset += 5;

    wire::write_u64_le(data + offset, transact_time_ ? static_cast<std::uint64_t>(transact_time_->count()) : static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL));
    offset += 8;

    return offset;
}

std::size_t PacketHeader::encoded_size() const {
    return wire_size;
}

void PacketHeader::print(std::ostream& out) const {
    out << "PacketHeader{";
    out << "eobi_header=";
    eobi_header_.print(out);
    out << ", appl_seq_num=";
    out << appl_seq_num_;
    out << ", market_segment_id=";
    print::optional(out, market_segment_id_);
    out << ", partition_id=";
    print::optional(out, partition_id_);
    out << ", completion_indicator=";
    print::optional(out, completion_indicator_);
    out << ", appl_seq_reset_indicator=";
    print::optional(out, appl_seq_reset_indicator_);
    out << ", pad5=";
    print::hex(out, pad5_.data(), pad5_.size());
    out << ", transact_time=";
    print::optional_duration(out, transact_time_);
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return eobi_header_ == other.eobi_header_
        && appl_seq_num_ == other.appl_seq_num_
        && market_segment_id_ == other.market_segment_id_
        && partition_id_ == other.partition_id_
        && completion_indicator_ == other.completion_indicator_
        && appl_seq_reset_indicator_ == other.appl_seq_reset_indicator_
        && pad5_ == other.pad5_
        && transact_time_ == other.transact_time_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
