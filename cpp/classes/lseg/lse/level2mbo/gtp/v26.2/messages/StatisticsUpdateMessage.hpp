#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/AuctionInfo.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/OpeningClosingPriceIndicator.hpp"
#include "../enums/SourceVenue.hpp"
#include "../enums/StatisticType.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Contains a set of statistics that are not updated frequently.
class StatisticsUpdateMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StatisticsUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 47;

    StatisticsUpdateMessage() = default;
    StatisticsUpdateMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, StatisticType statistic_type, Decimal statistic_price, Decimal statistic_size, AuctionType auction_type, Decimal imbalance_quantity, AuctionInfo auction_info, OpeningClosingPriceIndicator opening_closing_price_indicator);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Statistic Type: The statistic that is disseminated with this message instance.
    StatisticType statistic_type() const;
    void set_statistic_type(StatisticType value);

    // Statistic Price: The value of price type statistics. If the Opening or Closing Price is
    // cleared manually by the venue, '-1' will be stamped.
    Decimal statistic_price() const;
    void set_statistic_price(Decimal value);

    // Statistic Size: The value of size type statistics.
    Decimal statistic_size() const;
    void set_statistic_size(Decimal value);

    // Auction Type: The value in this field is only relevant when Trade Type is 1.
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Imbalance Quantity: Quantity that is eligible to be matched at the indicative price but
    // will not be matched.
    Decimal imbalance_quantity() const;
    void set_imbalance_quantity(Decimal value);

    // Auction Info: Populated if the Statistic Type is 1.
    AuctionInfo auction_info() const;
    void set_auction_info(AuctionInfo value);

    // Opening Closing Price Indicator: Populated if the Statistic Type is 2 or 3.
    OpeningClosingPriceIndicator opening_closing_price_indicator() const;
    void set_opening_closing_price_indicator(OpeningClosingPriceIndicator value);

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

    bool operator==(const StatisticsUpdateMessage& other) const;
    bool operator!=(const StatisticsUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t instrument_{};
    SourceVenue source_venue_{};
    StatisticType statistic_type_{};
    Decimal statistic_price_{ 0, -8 };
    Decimal statistic_size_{ 0, -8 };
    AuctionType auction_type_{};
    Decimal imbalance_quantity_{ 0, -8 };
    AuctionInfo auction_info_{};
    OpeningClosingPriceIndicator opening_closing_price_indicator_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
