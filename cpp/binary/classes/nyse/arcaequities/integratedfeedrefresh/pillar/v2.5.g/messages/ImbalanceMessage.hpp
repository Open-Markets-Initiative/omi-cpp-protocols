#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/AuctionStatus.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/FreezeStatus.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../enums/UnpairedSide.hpp"
#include "../messages/Message.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

class Visitor;

// Imbalance messages are published once a second during auctions to update price and volume
// information.
class ImbalanceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ImbalanceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 69;

    ImbalanceMessage() = default;
    ImbalanceMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::int32_t reference_price, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, std::uint16_t auction_time, AuctionType auction_type, ImbalanceSide imbalance_side, std::int32_t continuous_book_clearing_price, std::int32_t auction_interest_clearing_price, std::int32_t ssr_filing_price, std::int32_t indicative_match_price, std::int32_t upper_collar, std::int32_t lower_collar, AuctionStatus auction_status, FreezeStatus freeze_status, std::uint8_t num_extensions, std::uint32_t unpaired_qty, UnpairedSide unpaired_side, const std::array<std::byte, 1>& reserved_1);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

    // Source Time Ns: The nanosecond offset from the Source Time
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Symbol Index: The ID of the symbol in the Symbol Index msg
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: The sequence number of this message in the set of all messages for this
    // symbol
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Reference Price: The price at which imbalances are calculated.
    std::int32_t reference_price() const;
    void set_reference_price(std::int32_t value);

    // Paired Qty: Number of shares paired at the Reference Price.
    std::uint32_t paired_qty() const;
    void set_paired_qty(std::uint32_t value);

    // Total Imbalance Qty: The total imbalance quantity at the Reference Price.
    std::uint32_t total_imbalance_qty() const;
    void set_total_imbalance_qty(std::uint32_t value);

    // Market Imbalance Qty: The total market order imbalance quantity at the Reference Price.
    std::uint32_t market_imbalance_qty() const;
    void set_market_imbalance_qty(std::uint32_t value);

    // Auction Time: Projected Auction Time (hhmm)
    std::uint16_t auction_time() const;
    void set_auction_time(std::uint16_t value);

    // Auction Type: Auction type indicator.
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Imbalance Side: The side of the TotalImbalanceQty
    ImbalanceSide imbalance_side() const;
    void set_imbalance_side(ImbalanceSide value);

    // Continuous Book Clearing Price: The price closest to the reference price where the
    // imbalance is 0.
    std::int32_t continuous_book_clearing_price() const;
    void set_continuous_book_clearing_price(std::int32_t value);

    // Auction Interest Clearing Price: The price at which auction only interest would trade.
    std::int32_t auction_interest_clearing_price() const;
    void set_auction_interest_clearing_price(std::int32_t value);

    // Ssr Filing Price: For NYSE non-Significant imbalances, if a Sell Short Restriction is in
    // effect, the price at which Sell Short interest will be filed.
    std::int32_t ssr_filing_price() const;
    void set_ssr_filing_price(std::int32_t value);

    // Indicative Match Price: The best price at which the maximum volume of shares is
    // executable in the applicable auction, subject to Auction Collars.
    std::int32_t indicative_match_price() const;
    void set_indicative_match_price(std::int32_t value);

    // Upper Collar: Upper boundary for the Indicative Match Price.
    std::int32_t upper_collar() const;
    void set_upper_collar(std::int32_t value);

    // Lower Collar: Lower boundary for the Indicative Match Price.
    std::int32_t lower_collar() const;
    void set_lower_collar(std::int32_t value);

    // Auction Status: Indicates whether the auction will run.
    AuctionStatus auction_status() const;
    void set_auction_status(AuctionStatus value);

    // Freeze Status: Indicates an Imbalance Freeze for the auction.
    FreezeStatus freeze_status() const;
    void set_freeze_status(FreezeStatus value);

    // Num Extensions: The number of times a halt period has been extended
    std::uint8_t num_extensions() const;
    void set_num_extensions(std::uint8_t value);

    // Unpaired Qty: The number of unpaired shares priced at or better than the Reference
    // Price.
    std::uint32_t unpaired_qty() const;
    void set_unpaired_qty(std::uint32_t value);

    // Unpaired Side: The side of the Unpaired Qty
    UnpairedSide unpaired_side() const;
    void set_unpaired_side(UnpairedSide value);

    // Reserved 1: Reserved for future use
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const ImbalanceMessage& other) const;
    bool operator!=(const ImbalanceMessage& other) const;

  private:
    std::chrono::seconds source_time_{};
    std::chrono::nanoseconds source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::int32_t reference_price_{};
    std::uint32_t paired_qty_{};
    std::uint32_t total_imbalance_qty_{};
    std::uint32_t market_imbalance_qty_{};
    std::uint16_t auction_time_{};
    AuctionType auction_type_{};
    ImbalanceSide imbalance_side_{};
    std::int32_t continuous_book_clearing_price_{};
    std::int32_t auction_interest_clearing_price_{};
    std::int32_t ssr_filing_price_{};
    std::int32_t indicative_match_price_{};
    std::int32_t upper_collar_{};
    std::int32_t lower_collar_{};
    AuctionStatus auction_status_{};
    FreezeStatus freeze_status_{};
    std::uint8_t num_extensions_{};
    std::uint32_t unpaired_qty_{};
    UnpairedSide unpaired_side_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
