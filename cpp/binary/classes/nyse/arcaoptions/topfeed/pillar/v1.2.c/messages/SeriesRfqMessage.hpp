#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/Capacity.hpp"
#include "../enums/RfqStatus.hpp"
#include "../enums/Side.hpp"
#include "../enums/Type.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// The Request for Series RFQ message is published for outright series.
class SeriesRfqMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SeriesRfqMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 40;

    SeriesRfqMessage() = default;
    SeriesRfqMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, Side side, Type type_field, Capacity capacity, std::uint32_t total_quantity, std::int32_t working_price, std::uint32_t participant, std::uint64_t auction_id, RfqStatus rfq_status);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series for all products within this market
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Seq Num: The unique ID of this message in the sequence of messages published for
    // this specific series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Side: Side of the RFQ
    Side side() const;
    void set_side(Side value);

    // Type: Order Type of CUBE/Bold/COA
    Type type_field() const;
    void set_type_field(Type value);

    // Capacity: Customer or Firm capacity specified with the order. Values include:
    Capacity capacity() const;
    void set_capacity(Capacity value);

    // Total Quantity: Total quantity
    std::uint32_t total_quantity() const;
    void set_total_quantity(std::uint32_t value);

    // Working Price: RFQ Price
    std::int32_t working_price() const;
    void set_working_price(std::int32_t value);

    // Participant: OCC Number for the Clearing firm specified with the order.
    std::uint32_t participant() const;
    void set_participant(std::uint32_t value);

    // Auction Id: Auction ID for CUBE/COA
    std::uint64_t auction_id() const;
    void set_auction_id(std::uint64_t value);

    // Rfq Status: This status field is used for CUBE/COA (Type = C).
    RfqStatus rfq_status() const;
    void set_rfq_status(RfqStatus value);

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

    bool operator==(const SeriesRfqMessage& other) const;
    bool operator!=(const SeriesRfqMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    Side side_{};
    Type type_field_{};
    Capacity capacity_{};
    std::uint32_t total_quantity_{};
    std::int32_t working_price_{};
    std::uint32_t participant_{};
    std::uint64_t auction_id_{};
    RfqStatus rfq_status_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
