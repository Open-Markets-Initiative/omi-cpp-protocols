#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/MarketState.hpp"
#include "../enums/ShortSaleRestriction.hpp"
#include "../enums/TradingStatus.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This message is used to notify firms of changes to the trading status of a particular
// security.
class SecurityTradingStatusNotificationMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SecurityTradingStatusNotificationMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 11;

    SecurityTradingStatusNotificationMessage() = default;
    SecurityTradingStatusNotificationMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, TradingStatus trading_status, MarketState market_state, ShortSaleRestriction short_sale_restriction);

    // Nanoseconds: Nanosecond part of Matching Engine time.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Symbol Id: Symbol ID mapped to a given symbol. It is assigned per trading session and is
    // valid for that session.
    std::uint32_t symbol_id() const;
    void set_symbol_id(std::uint32_t value);

    // Trading Status: Current trading status of the security.
    TradingStatus trading_status() const;
    void set_trading_status(TradingStatus value);

    // Market State: Current market state.
    MarketState market_state() const;
    void set_market_state(MarketState value);

    // Short Sale Restriction: Current state of short sale restriction.
    ShortSaleRestriction short_sale_restriction() const;
    void set_short_sale_restriction(ShortSaleRestriction value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const SecurityTradingStatusNotificationMessage& other) const;
    bool operator!=(const SecurityTradingStatusNotificationMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    TradingStatus trading_status_{};
    MarketState market_state_{};
    ShortSaleRestriction short_sale_restriction_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
