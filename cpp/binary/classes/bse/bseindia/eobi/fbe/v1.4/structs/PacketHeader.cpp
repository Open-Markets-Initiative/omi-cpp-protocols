#include "PacketHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

PacketHeader::PacketHeader(const EobiHeader& eobi_header, std::uint32_t appl_seq_num, std::int32_t market_segment_id, std::uint8_t partition_id, std::uint8_t completion_indicator, std::uint8_t appl_seq_reset_indicator, const std::array<std::byte, 5>& pad_5, std::chrono::nanoseconds transact_time)
  : eobi_header_(eobi_header), appl_seq_num_(appl_seq_num), market_segment_id_(market_segment_id), partition_id_(partition_id), completion_indicator_(completion_indicator), appl_seq_reset_indicator_(appl_seq_reset_indicator), pad_5_(pad_5), transact_time_(transact_time) {}

const EobiHeader& PacketHeader::eobi_header() const { return eobi_header_; }
EobiHeader& PacketHeader::eobi_header() { return eobi_header_; }
void PacketHeader::set_eobi_header(const EobiHeader& value) { eobi_header_ = value; }

std::uint32_t PacketHeader::appl_seq_num() const { return appl_seq_num_; }
void PacketHeader::set_appl_seq_num(std::uint32_t value) { appl_seq_num_ = value; }

std::int32_t PacketHeader::market_segment_id() const { return market_segment_id_; }
void PacketHeader::set_market_segment_id(std::int32_t value) { market_segment_id_ = value; }

std::uint8_t PacketHeader::partition_id() const { return partition_id_; }
void PacketHeader::set_partition_id(std::uint8_t value) { partition_id_ = value; }

std::uint8_t PacketHeader::completion_indicator() const { return completion_indicator_; }
void PacketHeader::set_completion_indicator(std::uint8_t value) { completion_indicator_ = value; }

std::uint8_t PacketHeader::appl_seq_reset_indicator() const { return appl_seq_reset_indicator_; }
void PacketHeader::set_appl_seq_reset_indicator(std::uint8_t value) { appl_seq_reset_indicator_ = value; }

const std::array<std::byte, 5>& PacketHeader::pad_5() const { return pad_5_; }
std::array<std::byte, 5>& PacketHeader::pad_5() { return pad_5_; }
void PacketHeader::set_pad_5(const std::array<std::byte, 5>& value) { pad_5_ = value; }

std::chrono::nanoseconds PacketHeader::transact_time() const { return transact_time_; }
void PacketHeader::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::size_t PacketHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PacketHeader", wire_size, length);

    offset += eobi_header_.decode(data + offset, length - offset);

    appl_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_segment_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    partition_id_ = wire::read_u8(data + offset);
    offset += 1;

    completion_indicator_ = wire::read_u8(data + offset);
    offset += 1;

    appl_seq_reset_indicator_ = wire::read_u8(data + offset);
    offset += 1;

    wire::read_bytes(data + offset, pad_5_.data(), 5);
    offset += 5;

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    return offset;
}

std::size_t PacketHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PacketHeader", wire_size, capacity);

    offset += eobi_header_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(appl_seq_num_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(market_segment_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(partition_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(completion_indicator_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(appl_seq_reset_indicator_));
    offset += 1;

    wire::write_bytes(data + offset, pad_5_.data(), 5);
    offset += 5;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
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
    out << market_segment_id_;
    out << ", partition_id=";
    out << static_cast<int>(partition_id_);
    out << ", completion_indicator=";
    out << static_cast<int>(completion_indicator_);
    out << ", appl_seq_reset_indicator=";
    out << static_cast<int>(appl_seq_reset_indicator_);
    out << ", pad_5=";
    print::hex(out, pad_5_.data(), pad_5_.size());
    out << ", transact_time=";
    out << transact_time_.count();
    out << '}';
}

bool PacketHeader::operator==(const PacketHeader& other) const {
    return eobi_header_ == other.eobi_header_
        && appl_seq_num_ == other.appl_seq_num_
        && market_segment_id_ == other.market_segment_id_
        && partition_id_ == other.partition_id_
        && completion_indicator_ == other.completion_indicator_
        && appl_seq_reset_indicator_ == other.appl_seq_reset_indicator_
        && pad_5_ == other.pad_5_
        && transact_time_ == other.transact_time_;
}

bool PacketHeader::operator!=(const PacketHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
