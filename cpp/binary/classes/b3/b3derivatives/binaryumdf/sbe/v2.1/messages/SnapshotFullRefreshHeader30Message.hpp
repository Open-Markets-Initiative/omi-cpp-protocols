#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

class Visitor;

// SnapshotFullRefresh_Header_30Message
class SnapshotFullRefreshHeader30Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SnapshotFullRefreshHeader30Message;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 34;

    SnapshotFullRefreshHeader30Message() = default;
    SnapshotFullRefreshHeader30Message(std::uint64_t security_id, std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::uint32_t tot_num_bids, std::uint32_t tot_num_offers, std::uint16_t tot_num_stats, const std::array<std::byte, 2>& offset_26_padding_2, std::optional<std::uint32_t> last_rpt_seq, std::optional<std::uint16_t> last_sequence_version);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Last Msg Seq Num Processed: lastMsgSeqNumProcessed
    std::uint32_t last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::uint32_t value);

    // Tot Num Reports: totNumReports
    std::uint32_t tot_num_reports() const;
    void set_tot_num_reports(std::uint32_t value);

    // Tot Num Bids: totNumBids
    std::uint32_t tot_num_bids() const;
    void set_tot_num_bids(std::uint32_t value);

    // Tot Num Offers: totNumOffers
    std::uint32_t tot_num_offers() const;
    void set_tot_num_offers(std::uint32_t value);

    // Tot Num Stats: totNumStats
    std::uint16_t tot_num_stats() const;
    void set_tot_num_stats(std::uint16_t value);

    // Offset 26 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_26_padding_2() const;
    std::array<std::byte, 2>& offset_26_padding_2();
    void set_offset_26_padding_2(const std::array<std::byte, 2>& value);

    // Last Rpt Seq: lastRptSeq
    std::optional<std::uint32_t> last_rpt_seq() const;
    void set_last_rpt_seq(std::optional<std::uint32_t> value);

    // Last Sequence Version: lastSequenceVersion
    std::optional<std::uint16_t> last_sequence_version() const;
    void set_last_sequence_version(std::optional<std::uint16_t> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const SnapshotFullRefreshHeader30Message& other) const;
    bool operator!=(const SnapshotFullRefreshHeader30Message& other) const;

  private:
    std::uint64_t security_id_{};
    std::uint32_t last_msg_seq_num_processed_{};
    std::uint32_t tot_num_reports_{};
    std::uint32_t tot_num_bids_{};
    std::uint32_t tot_num_offers_{};
    std::uint16_t tot_num_stats_{};
    std::array<std::byte, 2> offset_26_padding_2_{};
    std::optional<std::uint32_t> last_rpt_seq_{};
    std::optional<std::uint16_t> last_sequence_version_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
