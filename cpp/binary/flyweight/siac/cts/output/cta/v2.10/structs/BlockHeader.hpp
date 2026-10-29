#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/RetransmissionIndicator.hpp"
#include "../structs/SipBlockTimestamp.hpp"

namespace siac::cts::output::cta::v2_10 {

// Cta Output packet header
class BlockHeader {
  public:
    static constexpr const char* name = "BlockHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit BlockHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every BlockHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::uint8_t version() const { return wire::read_u8(at(0)); }

    std::uint16_t block_size() const { return wire::read_u16_be(at(1)); }

    char data_feed_indicator() const { return wire::read_char(at(3)); }

    RetransmissionIndicator retransmission_indicator() const { return static_cast<RetransmissionIndicator>(wire::read_char(at(4))); }

    std::uint32_t block_sequence_number() const { return wire::read_u32_be(at(5)); }

    std::uint8_t messages_in_block() const { return wire::read_u8(at(9)); }

    SipBlockTimestamp sip_block_timestamp() const { return SipBlockTimestamp{ bytes_.subspan(10) }; }

    std::uint16_t block_checksum() const { return wire::read_u16_be(at(18)); }

    void print(std::ostream& out) const {
        out << "BlockHeader{";
        out << "version=";
        out << static_cast<int>(version());
        out << ", block_size=";
        out << block_size();
        out << ", data_feed_indicator=";
        print::character(out, data_feed_indicator());
        out << ", retransmission_indicator=";
        out << retransmission_indicator();
        out << ", block_sequence_number=";
        out << block_sequence_number();
        out << ", messages_in_block=";
        out << static_cast<int>(messages_in_block());
        out << ", sip_block_timestamp=";
        sip_block_timestamp().print(out);
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

} // namespace siac::cts::output::cta::v2_10
