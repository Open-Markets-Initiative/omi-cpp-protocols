#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/DataFeedIndicator.hpp"
#include "../enums/RetransmissionIndicator.hpp"
#include "../enums/SessionIndicator.hpp"
#include "../structs/BlockTimestamp.hpp"

namespace siac::opra::output::obi::v6_2 {

// Opra packet header
class BlockHeader {
  public:
    static constexpr const char* name = "BlockHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BlockHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BlockHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    std::uint8_t version() const { return wire::read_u8(at(0)); }

    std::uint16_t block_size() const { return wire::read_u16_be(at(1)); }

    DataFeedIndicator data_feed_indicator() const { return static_cast<DataFeedIndicator>(wire::read_char(at(3))); }

    RetransmissionIndicator retransmission_indicator() const { return static_cast<RetransmissionIndicator>(wire::read_char(at(4))); }

    SessionIndicator session_indicator() const { return static_cast<SessionIndicator>(wire::read_u8(at(5))); }

    std::uint32_t block_sequence_number() const { return wire::read_u32_be(at(6)); }

    std::uint8_t messages_in_block() const { return wire::read_u8(at(10)); }

    BlockTimestamp block_timestamp() const { return BlockTimestamp{ bytes_.subspan(11) }; }

    std::uint16_t block_checksum() const { return wire::read_u16_be(at(19)); }

    void print(std::ostream& out) const {
        out << "BlockHeader{";
        out << "version=";
        out << static_cast<int>(version());
        out << ", block_size=";
        out << block_size();
        out << ", data_feed_indicator=";
        out << data_feed_indicator();
        out << ", retransmission_indicator=";
        out << retransmission_indicator();
        out << ", session_indicator=";
        out << session_indicator();
        out << ", block_sequence_number=";
        out << block_sequence_number();
        out << ", messages_in_block=";
        out << static_cast<int>(messages_in_block());
        out << ", block_timestamp=";
        block_timestamp().print(out);
        out << ", block_checksum=";
        out << block_checksum();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const BlockHeader& value) {
    value.print(out);
    return out;
}

} // namespace siac::opra::output::obi::v6_2
