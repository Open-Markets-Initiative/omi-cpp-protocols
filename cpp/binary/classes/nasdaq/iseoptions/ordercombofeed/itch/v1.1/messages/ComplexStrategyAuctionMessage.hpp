#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../common/Day.hpp"
#include "../common/Decimal.hpp"
#include "../enums/AuctionEvent.hpp"
#include "../enums/AuctionType.hpp"
#include "../enums/ExecFlag.hpp"
#include "../enums/OrderCapacity.hpp"
#include "../enums/OrderType.hpp"
#include "../enums/Scope.hpp"
#include "../enums/Side.hpp"
#include "../groups/AuctionResponse.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

class Visitor;

// This message is used to announce strategy auctions. The start of auction is announced,
// followed by possible updates on the auction, and announcing the end of the auction.
class ComplexStrategyAuctionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::ComplexStrategyAuctionMessage;

    ComplexStrategyAuctionMessage() = default;
    ComplexStrategyAuctionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, std::uint32_t auction_id, OrderType order_type, Side side, Decimal price, std::uint32_t size, ExecFlag exec_flag, OrderCapacity order_capacity, Scope scope, const std::string& owner_id, const std::string& giveup, const std::string& cmta, AuctionEvent auction_event, AuctionType auction_type, std::uint8_t number_of_responses, const std::vector<AuctionResponse>& auction_response);

    // Timestamp: The time, expressed as the number of nanoseconds after midnight.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Strategy Id: ISE’s Strategy ID assigned daily, valid while there are any open complex
    // orders for the day
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

    // Auction Id: Integer which uniquely identifies the auction.
    std::uint32_t auction_id() const;
    void set_auction_id(std::uint32_t value);

    // Order Type: Order Type
    OrderType order_type() const;
    void set_order_type(OrderType value);

    // Side: ‘B’ = Bid ‘A’ = Offer (Ask) ‘ ’ (blank) = not set (hidden)
    Side side() const;
    void set_side(Side value);

    // Price: Price of the order in fixed point format with 6 whole number places followed by 4
    // decimal digits.
    Decimal price() const;
    void set_price(Decimal value);

    // Size: Size of the order
    std::uint32_t size() const;
    void set_size(std::uint32_t value);

    // Exec Flag: ‘N’ = None ‘A’ = AON
    ExecFlag exec_flag() const;
    void set_exec_flag(ExecFlag value);

    // Order Capacity: Order Capacity value
    OrderCapacity order_capacity() const;
    void set_order_capacity(OrderCapacity value);

    // Scope: Scope value
    Scope scope() const;
    void set_scope(Scope value);

    // Owner Id: Spaces when not set
    const std::string& owner_id() const;
    std::string& owner_id();
    void set_owner_id(const std::string& value);

    // Giveup: Spaces when not set
    const std::string& giveup() const;
    std::string& giveup();
    void set_giveup(const std::string& value);

    // Cmta: Spaces when not set
    const std::string& cmta() const;
    std::string& cmta();
    void set_cmta(const std::string& value);

    // Auction Event: ‘S’ = Start ‘U’ = Auction Update ‘E’ = End of Auction
    AuctionEvent auction_event() const;
    void set_auction_event(AuctionEvent value);

    // Auction Type: ‘E’ = Exposure ‘C’ = Facilitation ‘S’ = Solicitation ‘P’ = PIM
    AuctionType auction_type() const;
    void set_auction_type(AuctionType value);

    // Number Of Responses: Number of auction Responses. Next two fields repeat that number of
    // times. Allowable values for this field are 0 or 1.
    std::uint8_t number_of_responses() const;
    void set_number_of_responses(std::uint8_t value);

    // Auction Response: Auction Response information
    const std::vector<AuctionResponse>& auction_response() const;
    std::vector<AuctionResponse>& auction_response();
    void set_auction_response(const std::vector<AuctionResponse>& value);

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

    bool operator==(const ComplexStrategyAuctionMessage& other) const;
    bool operator!=(const ComplexStrategyAuctionMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    std::uint32_t auction_id_{};
    OrderType order_type_{};
    Side side_{};
    Decimal price_{ 0, -4 };
    std::uint32_t size_{};
    ExecFlag exec_flag_{};
    OrderCapacity order_capacity_{};
    Scope scope_{};
    std::string owner_id_{};
    std::string giveup_{};
    std::string cmta_{};
    AuctionEvent auction_event_{};
    AuctionType auction_type_{};
    std::uint8_t number_of_responses_{};
    std::vector<AuctionResponse> auction_response_{};
};

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
