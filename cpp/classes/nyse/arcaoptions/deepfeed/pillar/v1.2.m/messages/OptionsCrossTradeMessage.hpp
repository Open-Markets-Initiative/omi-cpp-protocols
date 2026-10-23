#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/CrossType.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Published on completion of a crossing from the opening and re-opening auction, showing the
// bulk volume that traded in the auction.
class OptionsCrossTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsCrossTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 25;

    OptionsCrossTradeMessage() = default;
    OptionsCrossTradeMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t cross_id, std::int32_t price, std::uint32_t volume, CrossType cross_type);

    // Source Time Ns: The nanosecond offset (UTC Time) from the Time Reference message.
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Series Index: The unique ID of this series within this market.
    std::uint32_t series_index() const;
    void set_series_index(std::uint32_t value);

    // Series Seq Num: The sequence number of this message in the set of all messages for this
    // series
    std::uint32_t series_seq_num() const;
    void set_series_seq_num(std::uint32_t value);

    // Cross Id: Unique identifier for this Cross Trade.
    std::uint32_t cross_id() const;
    void set_cross_id(std::uint32_t value);

    // Price: The order price. Use with the Price Scale from the series index mapping.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in contracts
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Cross Type: Reason for the crossing from the opening and re-opening auction.
    CrossType cross_type() const;
    void set_cross_type(CrossType value);

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

    bool operator==(const OptionsCrossTradeMessage& other) const;
    bool operator!=(const OptionsCrossTradeMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint32_t cross_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    CrossType cross_type_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
