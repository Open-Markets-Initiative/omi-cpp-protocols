#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../structs/EobiHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Technical header delivered in every Udp datagram, identifying the product, the partition,
// and the send time
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    PacketHeader() = default;
    PacketHeader(const EobiHeader& eobi_header, std::uint32_t appl_seq_num, std::int32_t market_segment_id, std::uint8_t partition_id, std::uint8_t completion_indicator, std::uint8_t appl_seq_reset_indicator, const std::array<std::byte, 5>& pad_5, std::chrono::nanoseconds transact_time);

    // Eobi Header: Body Len, Template Id, and Msg Seq Num opening the Packet Header
    const EobiHeader& eobi_header() const;
    EobiHeader& eobi_header();
    void set_eobi_header(const EobiHeader& value);

    // Appl Seq Num: Packet sequence number, contiguous and incremented per multicast address
    // and port
    std::uint32_t appl_seq_num() const;
    void set_appl_seq_num(std::uint32_t value);

    // Market Segment Id: Product identifier
    std::int32_t market_segment_id() const;
    void set_market_segment_id(std::int32_t value);

    // Partition Id: Grouping of Bse products
    std::uint8_t partition_id() const;
    void set_partition_id(std::uint8_t value);

    // Completion Indicator: Indicates whether a unit of work fits into a single datagram, 0
    // Incomplete and 1 Complete
    std::uint8_t completion_indicator() const;
    void set_completion_indicator(std::uint8_t value);

    // Appl Seq Reset Indicator: Set in the first packet header after a market data fail over
    // or restart, 0 No Reset and 1 Reset
    std::uint8_t appl_seq_reset_indicator() const;
    void set_appl_seq_reset_indicator(std::uint8_t value);

    // Pad 5: not used
    const std::array<std::byte, 5>& pad_5() const;
    std::array<std::byte, 5>& pad_5();
    void set_pad_5(const std::array<std::byte, 5>& value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PacketHeader& other) const;
    bool operator!=(const PacketHeader& other) const;

  private:
    EobiHeader eobi_header_{};
    std::uint32_t appl_seq_num_{};
    std::int32_t market_segment_id_{};
    std::uint8_t partition_id_{};
    std::uint8_t completion_indicator_{};
    std::uint8_t appl_seq_reset_indicator_{};
    std::array<std::byte, 5> pad_5_{};
    std::chrono::nanoseconds transact_time_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace bse::bseindia::eobi::fbe::v1_4
