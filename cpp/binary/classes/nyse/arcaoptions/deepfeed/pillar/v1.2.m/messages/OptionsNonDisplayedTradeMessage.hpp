#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/NonDisplayedTradeTradeCond1.hpp"
#include "../enums/PriceType.hpp"
#include "../enums/PrintableFlag.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class Visitor;

// Published as a result of a match between two non-displayed orders.
class OptionsNonDisplayedTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsNonDisplayedTradeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 30;

    OptionsNonDisplayedTradeMessage() = default;
    OptionsNonDisplayedTradeMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1, const std::array<std::byte, 3>& reserved_3, PriceType price_type);

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

    // Trade Id: Unique ID assigned by the matching engine to this execution.
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Price: The order price. Use with the Price Scale from the series index mapping.
    std::int32_t price() const;
    void set_price(std::int32_t value);

    // Volume: The order quantity in contracts
    std::uint32_t volume() const;
    void set_volume(std::uint32_t value);

    // Printable Flag: Indicates whether trade is included in total volume.
    PrintableFlag printable_flag() const;
    void set_printable_flag(PrintableFlag value);

    // Non Displayed Trade Trade Cond 1: Settlement related conditions.
    NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1() const;
    void set_non_displayed_trade_trade_cond_1(NonDisplayedTradeTradeCond1 value);

    // Reserved 3: Reserved for future use
    const std::array<std::byte, 3>& reserved_3() const;
    std::array<std::byte, 3>& reserved_3();
    void set_reserved_3(const std::array<std::byte, 3>& value);

    // Price Type: Price type indicator.
    PriceType price_type() const;
    void set_price_type(PriceType value);

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

    bool operator==(const OptionsNonDisplayedTradeMessage& other) const;
    bool operator!=(const OptionsNonDisplayedTradeMessage& other) const;

  private:
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::uint32_t trade_id_{};
    std::int32_t price_{};
    std::uint32_t volume_{};
    PrintableFlag printable_flag_{};
    NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1_{};
    std::array<std::byte, 3> reserved_3_{};
    PriceType price_type_{};
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
