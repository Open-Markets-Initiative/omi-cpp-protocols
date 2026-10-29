#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/ListingMarket.hpp"
#include "../messages/Message.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class Visitor;

// Reference data for each symbol that may be traded
class SymbolInformationMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SymbolInformationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 26;

    SymbolInformationMessage() = default;
    SymbolInformationMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, const std::string& symbol, ListingMarket listing_market, std::uint32_t board_lot_size);

    // Timestamp: Nanoseconds Since Epoch (UTC)
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol Id: Symbol Index
    std::uint16_t symbol_id() const;
    void set_symbol_id(std::uint16_t value);

    // Symbol: Stock Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Listing Market: Code identifying the primary listing market
    ListingMarket listing_market() const;
    void set_listing_market(ListingMarket value);

    // Board Lot Size: Board Lot Size in Shares
    std::uint32_t board_lot_size() const;
    void set_board_lot_size(std::uint32_t value);

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

    bool operator==(const SymbolInformationMessage& other) const;
    bool operator!=(const SymbolInformationMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t symbol_id_{};
    std::string symbol_{};
    ListingMarket listing_market_{};
    std::uint32_t board_lot_size_{};
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
