// Databento.MarketData.Normalized.Dbn.v2: messages/ImbalanceMsg.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Side.hpp"
#include "../enums/UnpairedSide.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

class Visitor;

// An auction imbalance message; the record of the imbalance schema
class ImbalanceMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Imbalance;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 96;

    ImbalanceMsg() = default;
    ImbalanceMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<Decimal> ref_price, std::optional<std::chrono::nanoseconds> auction_time, std::optional<Decimal> cont_book_clr_price, std::optional<Decimal> auct_interest_clr_price, std::optional<Decimal> ssr_filling_price, std::optional<Decimal> ind_match_price, std::optional<Decimal> upper_collar, std::optional<Decimal> lower_collar, std::uint32_t paired_qty, std::uint32_t total_imbalance_qty, std::uint32_t market_imbalance_qty, std::uint32_t unpaired_qty, char auction_type, Side side, std::uint8_t auction_status, std::uint8_t freeze_status, std::uint8_t num_extensions, UnpairedSide unpaired_side, char significant_imbalance, const std::array<std::byte, 1>& reserved_1);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Ref Price: The price at which the imbalance shares are calculated
    std::optional<Decimal> ref_price() const;
    void set_ref_price(std::optional<Decimal> value);

    // Auction Time: Reserved for future use
    std::optional<std::chrono::nanoseconds> auction_time() const;
    void set_auction_time(std::optional<std::chrono::nanoseconds> value);

    // Cont Book Clr Price: The hypothetical auction-clearing price for both cross and
    // continuous orders
    std::optional<Decimal> cont_book_clr_price() const;
    void set_cont_book_clr_price(std::optional<Decimal> value);

    // Auct Interest Clr Price: The hypothetical auction-clearing price for cross orders only
    std::optional<Decimal> auct_interest_clr_price() const;
    void set_auct_interest_clr_price(std::optional<Decimal> value);

    // Ssr Filling Price: Reserved for future use
    std::optional<Decimal> ssr_filling_price() const;
    void set_ssr_filling_price(std::optional<Decimal> value);

    // Ind Match Price: Reserved for future use
    std::optional<Decimal> ind_match_price() const;
    void set_ind_match_price(std::optional<Decimal> value);

    // Upper Collar: Reserved for future use
    std::optional<Decimal> upper_collar() const;
    void set_upper_collar(std::optional<Decimal> value);

    // Lower Collar: Reserved for future use
    std::optional<Decimal> lower_collar() const;
    void set_lower_collar(std::optional<Decimal> value);

    // Paired Qty: The quantity of shares that are eligible to be matched at ref_price
    std::uint32_t paired_qty() const;
    void set_paired_qty(std::uint32_t value);

    // Total Imbalance Qty: The quantity of shares that are not paired at ref_price
    std::uint32_t total_imbalance_qty() const;
    void set_total_imbalance_qty(std::uint32_t value);

    // Market Imbalance Qty: Reserved for future use
    std::uint32_t market_imbalance_qty() const;
    void set_market_imbalance_qty(std::uint32_t value);

    // Unpaired Qty: Reserved for future use
    std::uint32_t unpaired_qty() const;
    void set_unpaired_qty(std::uint32_t value);

    // Auction Type: Venue-specific character code indicating the auction type; ~ when unused
    char auction_type() const;
    void set_auction_type(char value);

    // Side: The side that initiates the event
    Side side() const;
    void set_side(Side value);

    // Auction Status: Reserved for future use
    std::uint8_t auction_status() const;
    void set_auction_status(std::uint8_t value);

    // Freeze Status: Reserved for future use
    std::uint8_t freeze_status() const;
    void set_freeze_status(std::uint8_t value);

    // Num Extensions: Reserved for future use
    std::uint8_t num_extensions() const;
    void set_num_extensions(std::uint8_t value);

    // Unpaired Side: Reserved for future use
    UnpairedSide unpaired_side() const;
    void set_unpaired_side(UnpairedSide value);

    // Significant Imbalance: Venue-specific character code; for Nasdaq, contains the raw Price
    // Variation Indicator
    char significant_imbalance() const;
    void set_significant_imbalance(char value);

    // Reserved 1: Reserved, 1 byte
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

    bool operator==(const ImbalanceMsg& other) const;
    bool operator!=(const ImbalanceMsg& other) const;

  private:
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::optional<Decimal> ref_price_{};
    std::optional<std::chrono::nanoseconds> auction_time_{};
    std::optional<Decimal> cont_book_clr_price_{};
    std::optional<Decimal> auct_interest_clr_price_{};
    std::optional<Decimal> ssr_filling_price_{};
    std::optional<Decimal> ind_match_price_{};
    std::optional<Decimal> upper_collar_{};
    std::optional<Decimal> lower_collar_{};
    std::uint32_t paired_qty_{};
    std::uint32_t total_imbalance_qty_{};
    std::uint32_t market_imbalance_qty_{};
    std::uint32_t unpaired_qty_{};
    char auction_type_{};
    Side side_{};
    std::uint8_t auction_status_{};
    std::uint8_t freeze_status_{};
    std::uint8_t num_extensions_{};
    UnpairedSide unpaired_side_{};
    char significant_imbalance_{};
    std::array<std::byte, 1> reserved_1_{};
};

} // namespace databento::marketdata::normalized::dbn::v2
