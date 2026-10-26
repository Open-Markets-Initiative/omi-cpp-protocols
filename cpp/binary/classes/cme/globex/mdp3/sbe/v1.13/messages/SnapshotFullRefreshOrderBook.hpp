#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/MktdataPayload.hpp"
#include "../structs/SnapshotFullRefreshOrderBookGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MktdataPayloadVisitor;

// SnapshotFullRefreshOrderBook
class SnapshotFullRefreshOrderBook : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::SnapshotFullRefreshOrderBook;

    SnapshotFullRefreshOrderBook() = default;
    SnapshotFullRefreshOrderBook(std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::int32_t security_id, std::uint32_t no_chunks, std::uint32_t current_chunk, std::chrono::nanoseconds transact_time, const SnapshotFullRefreshOrderBookGroups& snapshot_full_refresh_order_book_groups);

    // Last Msg Seq Num Processed: Sequence number of the last Incremental feed packet
    // processed. This value is used to synchronize the snapshot loop with the real-time feed
    std::uint32_t last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::uint32_t value);

    // Tot Num Reports: Total number of messages replayed in the loop
    std::uint32_t tot_num_reports() const;
    void set_tot_num_reports(std::uint32_t value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // No Chunks: Total number of packets that constitutes a single instrument order book
    std::uint32_t no_chunks() const;
    void set_no_chunks(std::uint32_t value);

    // Current Chunk: Chunk sequence
    std::uint32_t current_chunk() const;
    void set_current_chunk(std::uint32_t value);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Snapshot Full Refresh Order Book Groups: NoMDEntries Block
    const SnapshotFullRefreshOrderBookGroups& snapshot_full_refresh_order_book_groups() const;
    SnapshotFullRefreshOrderBookGroups& snapshot_full_refresh_order_book_groups();
    void set_snapshot_full_refresh_order_book_groups(const SnapshotFullRefreshOrderBookGroups& value);

    // MktdataPayload
    MktdataPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MktdataPayloadVisitor& visitor) const override;
    std::unique_ptr<MktdataPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MktdataPayload& other) const override;

    bool operator==(const SnapshotFullRefreshOrderBook& other) const;
    bool operator!=(const SnapshotFullRefreshOrderBook& other) const;

  private:
    std::uint32_t last_msg_seq_num_processed_{};
    std::uint32_t tot_num_reports_{};
    std::int32_t security_id_{};
    std::uint32_t no_chunks_{};
    std::uint32_t current_chunk_{};
    std::chrono::nanoseconds transact_time_{};
    SnapshotFullRefreshOrderBookGroups snapshot_full_refresh_order_book_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
