#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/HaltCondition.hpp"
#include "../enums/MarketState.hpp"
#include "../enums/SeriesStatus.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// This message informs clients of changes in the status of a specific option outright series
// and complex series
class OptionsStatusMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    OptionsStatusMessage() = default;
    OptionsStatusMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, SeriesStatus series_status, MarketState market_state, HaltCondition halt_condition);

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

    // Series Status: The new status that this series is transitioning to
    SeriesStatus series_status() const;
    void set_series_status(SeriesStatus value);

    // Market State: The current Market State, which this msg updates if the Security Status
    // field contains a Market State Code.
    MarketState market_state() const;
    void set_market_state(MarketState value);

    // Halt Condition: Halt condition indicator
    HaltCondition halt_condition() const;
    void set_halt_condition(HaltCondition value);

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

    bool operator==(const OptionsStatusMessage& other) const;
    bool operator!=(const OptionsStatusMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    SeriesStatus series_status_{};
    MarketState market_state_{};
    HaltCondition halt_condition_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
