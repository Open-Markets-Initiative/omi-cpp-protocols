#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/ApplSeqResetIndicator.hpp"
#include "../enums/CompletionIndicator.hpp"
#include "../structs/EobiHeader.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

// Eurex Eobi Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    PacketHeader() = default;
    PacketHeader(const EobiHeader& eobi_header, std::uint32_t appl_seq_num, std::optional<std::int32_t> market_segment_id, std::optional<std::uint8_t> partition_id, std::optional<CompletionIndicator> completion_indicator, std::optional<ApplSeqResetIndicator> appl_seq_reset_indicator, std::uint8_t dscp, const std::array<std::byte, 4>& pad4, std::optional<std::chrono::nanoseconds> transact_time);

    // Eobi Header: EOBI PacketHeader MessageHeaderComp (BodyLen + TemplateID + MsgSeqNum) —
    // first 8 bytes of every Eurex T7 EOBI packet.
    const EobiHeader& eobi_header() const;
    EobiHeader& eobi_header();
    void set_eobi_header(const EobiHeader& value);

    // Appl Seq Num: Application sequence number per Market Segment / Partition
    std::uint32_t appl_seq_num() const;
    void set_appl_seq_num(std::uint32_t value);

    // Market Segment Id: Market Segment identifier for the partition
    std::optional<std::int32_t> market_segment_id() const;
    void set_market_segment_id(std::optional<std::int32_t> value);

    // Partition Id: Partition identifier within the market segment
    std::optional<std::uint8_t> partition_id() const;
    void set_partition_id(std::optional<std::uint8_t> value);

    // Completion Indicator: End-of-event marker (0 = more to follow, 1 = last packet of event)
    std::optional<CompletionIndicator> completion_indicator() const;
    void set_completion_indicator(std::optional<CompletionIndicator> value);

    // Appl Seq Reset Indicator: Indicates whether Application Sequence Number was reset for
    // this Market Segment
    std::optional<ApplSeqResetIndicator> appl_seq_reset_indicator() const;
    void set_appl_seq_reset_indicator(std::optional<ApplSeqResetIndicator> value);

    // DSCP: Copy of DSCP from IP protocol header
    std::uint8_t dscp() const;
    void set_dscp(std::uint8_t value);

    // Pad4:
    const std::array<std::byte, 4>& pad4() const;
    std::array<std::byte, 4>& pad4();
    void set_pad4(const std::array<std::byte, 4>& value);

    // Transact Time: Matching-engine transaction time in nanoseconds since Unix epoch
    std::optional<std::chrono::nanoseconds> transact_time() const;
    void set_transact_time(std::optional<std::chrono::nanoseconds> value);

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
    std::optional<std::int32_t> market_segment_id_{};
    std::optional<std::uint8_t> partition_id_{};
    std::optional<CompletionIndicator> completion_indicator_{};
    std::optional<ApplSeqResetIndicator> appl_seq_reset_indicator_{};
    std::uint8_t dscp_{};
    std::array<std::byte, 4> pad4_{};
    std::optional<std::chrono::nanoseconds> transact_time_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace eurex::t7::eobi::fbe::v13_0
