#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/AuctionStatus.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/FreezeStatus.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../messages/Message.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

class Visitor;

// Imbalance messages are sent periodically during auctions to update price and volume
// information. If there is no change to the calculated fields, no message will be generated.
class ImbalanceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ImbalanceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 63;

    ImbalanceMessage() = default;
    ImbalanceMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t reference_price, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, std::uint16_t auction_time, AuctionType auction_type, ImbalanceSide imbalance_side, std::uint32_t continuous_book_clearing_price, std::uint32_t closing_only_clearing_price, std::uint32_t ssr_filing_price, std::uint32_t indicative_match_price, std::uint32_t upper_collar, std::uint32_t lower_collar, AuctionStatus auction_status, FreezeStatus freeze_status, std::uint8_t num_extensions);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::uint32_t source_time() const;
    void set_source_time(std::uint32_t value);

    // Source Time Ns: The nanosecond offset from the SourceTime
    std::uint32_t source_time_ns() const;
    void set_source_time_ns(std::uint32_t value);

    // Symbol Index: The unique ID of this symbol for all products within this market. This ID
    // cannot be used to cross reference a security between markets.
    std::uint32_t symbol_index() const;
    void set_symbol_index(std::uint32_t value);

    // Symbol Seq Num: Reserved for future use. Ignore any content. This usage will become
    // standard across all products in future releases.
    std::uint32_t symbol_seq_num() const;
    void set_symbol_seq_num(std::uint32_t value);

    // Reference Price: For Pillar-powered markets, the Reference Price is used to calculate
    // the Indicative Match Price. For NYSE Tape A symbols, the Reference Price is the Last
    // Sale if the last sale is at or between the current best quote.
    std::uint32_t reference_price() const;
    void set_reference_price(std::uint32_t value);

    // Paired Qty: For Pillar-powered markets, the number of shares paired off at the
    // Indicative Match Price. For NYSE, the number of shares paired off at the Reference
    // Price, truncated to the nearest round lot quantity.
    std::uint32_t paired_qty() const;
    void set_paired_qty(std::uint32_t value);

    // Total Imbalance Qty: For Pillar-powered markets, the total imbalance quantity at the
    // Indicative Match Price. For NYSE, the total imbalance quantity at the Reference Price,
    // truncated to the round lot.
    std::uint32_t total_imbalance_qty() const;
    void set_total_imbalance_qty(std::uint32_t value);

    // Market Imbalance Qty: For Pillar-powered markets, the total market order imbalance
    // quantity at the Indicative Match Price.
    std::uint32_t market_imbalance_qty() const;
    void set_market_imbalance_qty(std::uint32_t value);

    // Auction Time: Projected Auction Time (hhmm)
    std::uint16_t auction_time() const;
    void set_auction_time(std::uint16_t value);

    // Auction Type: Type of auction
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Imbalance Side: The side of the TotalImbalanceQty
    ImbalanceSide imbalance_side() const;
    void set_imbalance_side(ImbalanceSide value);

    // Continuous Book Clearing Price: For Pillar-powered markets, the price at which all
    // interest on the book can trade, including auction and imbalance offset interest, and
    // disregarding auction collars. For NYSE, the indicative matching price, i.e. the price
    // closest to the reference price where the imbalance is 0. If a continuous book clearing
    // price is not reached, it is defaulted to 0.
    std::uint32_t continuous_book_clearing_price() const;
    void set_continuous_book_clearing_price(std::uint32_t value);

    // Closing Only Clearing Price: For Pillar-powered markets, the price at which all eligible
    // auction-only interest would trade, subject to auction collars For NYSE, the price
    // closest to the reference price where the imbalance of closing-only interest is 0. If a
    // closing-only clearing price is not reached, it is defaulted to 0.
    std::uint32_t closing_only_clearing_price() const;
    void set_closing_only_clearing_price(std::uint32_t value);

    // Ssr Filing Price: For Pillar-powered markets, not supported and defaulted to 0. For
    // NYSE, the price at which Sell Short interest in the opening auction will be filed if a
    // Sell Short Restriction is in effect for the security.
    std::uint32_t ssr_filing_price() const;
    void set_ssr_filing_price(std::uint32_t value);

    // Indicative Match Price: For Pillar-powered markets, the price that has the highest
    // executable volume of auction-eligible shares, subject to auction collars. It includes
    // the non-displayed quantity of Reserve Orders.
    std::uint32_t indicative_match_price() const;
    void set_indicative_match_price(std::uint32_t value);

    // Upper Collar: If the IndicativeMatchPrice is not strictly between the UpperCollar and
    // the LowerCollar, special auction rules apply. See Rule 7.35P for details.
    std::uint32_t upper_collar() const;
    void set_upper_collar(std::uint32_t value);

    // Lower Collar: If the IndicativeMatchPrice is not strictly between the UpperCollar and
    // the LowerCollar, special auction rules apply. See Rule 7.35P for details.
    std::uint32_t lower_collar() const;
    void set_lower_collar(std::uint32_t value);

    // Auction Status: Indicates whether the auction will run
    AuctionStatus auction_status() const;
    void set_auction_status(AuctionStatus value);

    // Freeze Status: Freeze status code
    FreezeStatus freeze_status() const;
    void set_freeze_status(FreezeStatus value);

    // Num Extensions: Number of times the halt period has been extended
    std::uint8_t num_extensions() const;
    void set_num_extensions(std::uint8_t value);

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
    std::uint32_t source_time_{};
    std::uint32_t source_time_ns_{};
    std::uint32_t symbol_index_{};
    std::uint32_t symbol_seq_num_{};
    std::uint32_t reference_price_{};
    std::uint32_t paired_qty_{};
    std::uint32_t total_imbalance_qty_{};
    std::uint32_t market_imbalance_qty_{};
    std::uint16_t auction_time_{};
    AuctionType auction_type_{};
    ImbalanceSide imbalance_side_{};
    std::uint32_t continuous_book_clearing_price_{};
    std::uint32_t closing_only_clearing_price_{};
    std::uint32_t ssr_filing_price_{};
    std::uint32_t indicative_match_price_{};
    std::uint32_t upper_collar_{};
    std::uint32_t lower_collar_{};
    AuctionStatus auction_status_{};
    FreezeStatus freeze_status_{};
    std::uint8_t num_extensions_{};
};

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
