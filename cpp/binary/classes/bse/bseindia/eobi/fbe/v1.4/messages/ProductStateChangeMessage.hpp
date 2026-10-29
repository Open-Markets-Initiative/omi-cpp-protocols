#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/FastMarketIndicator.hpp"
#include "../enums/TradSesStatus.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TradingSessionSubId.hpp"
#include "../messages/Message.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

class Visitor;

// Provides updates on the trading state for all instruments in a particular product.
class ProductStateChangeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ProductStateChangeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    ProductStateChangeMessage() = default;
    ProductStateChangeMessage(TradingSessionId trading_session_id, TradingSessionSubId trading_session_sub_id, TradSesStatus trad_ses_status, FastMarketIndicator fast_market_indicator, const std::array<std::byte, 4>& pad_4, std::chrono::nanoseconds transact_time);

    // Trading Session Id: Miscellaneous state information.
    TradingSessionId trading_session_id() const;
    void set_trading_session_id(TradingSessionId value);

    // Trading Session Sub Id: Product state information.
    TradingSessionSubId trading_session_sub_id() const;
    void set_trading_session_sub_id(TradingSessionSubId value);

    // Trad Ses Status: Miscellaneous state information.
    TradSesStatus trad_ses_status() const;
    void set_trad_ses_status(TradSesStatus value);

    // Fast Market Indicator: Indicates if product is in the state Fast Market.
    FastMarketIndicator fast_market_indicator() const;
    void set_fast_market_indicator(FastMarketIndicator value);

    // Pad 4: not used
    const std::array<std::byte, 4>& pad_4() const;
    std::array<std::byte, 4>& pad_4();
    void set_pad_4(const std::array<std::byte, 4>& value);

    // Transact Time: Transaction timestamp.
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

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

    bool operator==(const ProductStateChangeMessage& other) const;
    bool operator!=(const ProductStateChangeMessage& other) const;

  private:
    TradingSessionId trading_session_id_{};
    TradingSessionSubId trading_session_sub_id_{};
    TradSesStatus trad_ses_status_{};
    FastMarketIndicator fast_market_indicator_{};
    std::array<std::byte, 4> pad_4_{};
    std::chrono::nanoseconds transact_time_{};
};

} // namespace bse::bseindia::eobi::fbe::v1_4
