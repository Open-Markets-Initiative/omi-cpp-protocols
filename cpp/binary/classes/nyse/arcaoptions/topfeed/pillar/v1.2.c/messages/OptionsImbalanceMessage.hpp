#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/AuctionStatus.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class Visitor;

// Options Imbalance messages are published once a second during opening and reopening auctions
// to update price and volume information
class OptionsImbalanceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsImbalanceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 61;

    OptionsImbalanceMessage() = default;
    OptionsImbalanceMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, const std::array<std::byte, 4>& reserved_4, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, const std::array<std::byte, 2>& reserved_2, AuctionType auction_type, ImbalanceSide imbalance_side, std::int32_t continuous_book_clearing_price, std::int32_t auction_interest_clearing_price, const std::array<std::byte, 4>& second_reserved_4, std::int32_t indicative_match_price, std::int32_t upper_collar, std::int32_t lower_collar, AuctionStatus auction_status);

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

    // Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Paired Qty: The number of contracts paired off at the Indicative Match Price.
    std::uint32_t paired_qty() const;
    void set_paired_qty(std::uint32_t value);

    // Total Imbalance Qty: The total imbalance quantity at the Indicative Match Price.
    std::uint32_t total_imbalance_qty() const;
    void set_total_imbalance_qty(std::uint32_t value);

    // Market Imbalance Qty: The total market order imbalance quantity at the Indicative Match
    // Price.
    std::uint32_t market_imbalance_qty() const;
    void set_market_imbalance_qty(std::uint32_t value);

    // Reserved 2: Reserved for future use
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Auction Type: AuctionType
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Imbalance Side: The side of the TotalImbalanceQty
    ImbalanceSide imbalance_side() const;
    void set_imbalance_side(ImbalanceSide value);

    // Continuous Book Clearing Price: The price at which all interest on the book can trade,
    // including auction and imbalance offset interest, and disregarding auction collars.
    std::int32_t continuous_book_clearing_price() const;
    void set_continuous_book_clearing_price(std::int32_t value);

    // Auction Interest Clearing Price: The price at which all eligible auction-only interest
    // would trade, subject to auction collars.
    std::int32_t auction_interest_clearing_price() const;
    void set_auction_interest_clearing_price(std::int32_t value);

    // Second Reserved 4: Reserved for future use
    const std::array<std::byte, 4>& second_reserved_4() const;
    std::array<std::byte, 4>& second_reserved_4();
    void set_second_reserved_4(const std::array<std::byte, 4>& value);

    // Indicative Match Price: The price at which the highest number of contracts would trade,
    // subject to auction collars. It includes the non-displayed quantity of Reserve Orders.
    // See Information on Auctions for details.
    std::int32_t indicative_match_price() const;
    void set_indicative_match_price(std::int32_t value);

    // Upper Collar: Legal width bid for option
    std::int32_t upper_collar() const;
    void set_upper_collar(std::int32_t value);

    // Lower Collar: Legal width offer for option
    std::int32_t lower_collar() const;
    void set_lower_collar(std::int32_t value);

    // Auction Status: Indicates whether the auction will run
    AuctionStatus auction_status() const;
    void set_auction_status(AuctionStatus value);

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

    bool operator==(const OptionsImbalanceMessage& other) const;
    bool operator!=(const OptionsImbalanceMessage& other) const;

  private:
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t series_index_{};
    std::uint32_t series_seq_num_{};
    std::array<std::byte, 4> reserved_4_{};
    std::uint32_t paired_qty_{};
    std::uint32_t total_imbalance_qty_{};
    std::uint32_t market_imbalance_qty_{};
    std::array<std::byte, 2> reserved_2_{};
    AuctionType auction_type_{};
    ImbalanceSide imbalance_side_{};
    std::int32_t continuous_book_clearing_price_{};
    std::int32_t auction_interest_clearing_price_{};
    std::array<std::byte, 4> second_reserved_4_{};
    std::int32_t indicative_match_price_{};
    std::int32_t upper_collar_{};
    std::int32_t lower_collar_{};
    AuctionStatus auction_status_{};
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
