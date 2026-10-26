#include "BlockHeader.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace siac::cqs::output::cta::v2_10_a {

BlockHeader::BlockHeader(std::uint8_t version, std::uint16_t block_size, char data_feed_indicator, char retransmission_indicator, std::uint32_t block_sequence_number, std::uint8_t messages_in_block, const SipBlockTimestamp& sip_block_timestamp, std::uint16_t block_checksum)
  : version_(version), block_size_(block_size), data_feed_indicator_(data_feed_indicator), retransmission_indicator_(retransmission_indicator), block_sequence_number_(block_sequence_number), messages_in_block_(messages_in_block), sip_block_timestamp_(sip_block_timestamp), block_checksum_(block_checksum) {}

std::uint8_t BlockHeader::version() const { return version_; }
void BlockHeader::set_version(std::uint8_t value) { version_ = value; }

std::uint16_t BlockHeader::block_size() const { return block_size_; }
void BlockHeader::set_block_size(std::uint16_t value) { block_size_ = value; }

char BlockHeader::data_feed_indicator() const { return data_feed_indicator_; }
void BlockHeader::set_data_feed_indicator(char value) { data_feed_indicator_ = value; }

char BlockHeader::retransmission_indicator() const { return retransmission_indicator_; }
void BlockHeader::set_retransmission_indicator(char value) { retransmission_indicator_ = value; }

std::uint32_t BlockHeader::block_sequence_number() const { return block_sequence_number_; }
void BlockHeader::set_block_sequence_number(std::uint32_t value) { block_sequence_number_ = value; }

std::uint8_t BlockHeader::messages_in_block() const { return messages_in_block_; }
void BlockHeader::set_messages_in_block(std::uint8_t value) { messages_in_block_ = value; }

const SipBlockTimestamp& BlockHeader::sip_block_timestamp() const { return sip_block_timestamp_; }
SipBlockTimestamp& BlockHeader::sip_block_timestamp() { return sip_block_timestamp_; }
void BlockHeader::set_sip_block_timestamp(const SipBlockTimestamp& value) { sip_block_timestamp_ = value; }

std::uint16_t BlockHeader::block_checksum() const { return block_checksum_; }
void BlockHeader::set_block_checksum(std::uint16_t value) { block_checksum_ = value; }

std::size_t BlockHeader::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("BlockHeader", wire_size, length);

    version_ = wire::read_u8(data + offset);
    offset += 1;

    block_size_ = wire::read_u16_be(data + offset);
    offset += 2;

    data_feed_indicator_ = wire::read_char(data + offset);
    offset += 1;

    retransmission_indicator_ = wire::read_char(data + offset);
    offset += 1;

    block_sequence_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    messages_in_block_ = wire::read_u8(data + offset);
    offset += 1;

    offset += sip_block_timestamp_.decode(data + offset, length - offset);

    block_checksum_ = wire::read_u16_be(data + offset);
    offset += 2;

    return offset;
}

std::size_t BlockHeader::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BlockHeader", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(block_size_));
    offset += 2;

    wire::write_char(data + offset, data_feed_indicator_);
    offset += 1;

    wire::write_char(data + offset, retransmission_indicator_);
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(block_sequence_number_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(messages_in_block_));
    offset += 1;

    offset += sip_block_timestamp_.encode(data + offset, capacity - offset);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(block_checksum_));
    offset += 2;

    return offset;
}

std::size_t BlockHeader::encoded_size() const {
    return wire_size;
}

void BlockHeader::print(std::ostream& out) const {
    out << "BlockHeader{";
    out << "version=";
    out << static_cast<int>(version_);
    out << ", block_size=";
    out << block_size_;
    out << ", data_feed_indicator=";
    print::character(out, data_feed_indicator_);
    out << ", retransmission_indicator=";
    print::character(out, retransmission_indicator_);
    out << ", block_sequence_number=";
    out << block_sequence_number_;
    out << ", messages_in_block=";
    out << static_cast<int>(messages_in_block_);
    out << ", sip_block_timestamp=";
    sip_block_timestamp_.print(out);
    out << ", block_checksum=";
    out << block_checksum_;
    out << '}';
}

bool BlockHeader::operator==(const BlockHeader& other) const {
    return version_ == other.version_
        && block_size_ == other.block_size_
        && data_feed_indicator_ == other.data_feed_indicator_
        && retransmission_indicator_ == other.retransmission_indicator_
        && block_sequence_number_ == other.block_sequence_number_
        && messages_in_block_ == other.messages_in_block_
        && sip_block_timestamp_ == other.sip_block_timestamp_
        && block_checksum_ == other.block_checksum_;
}

bool BlockHeader::operator!=(const BlockHeader& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BlockHeader& value) {
    value.print(out);
    return out;
}

} // namespace siac::cqs::output::cta::v2_10_a
