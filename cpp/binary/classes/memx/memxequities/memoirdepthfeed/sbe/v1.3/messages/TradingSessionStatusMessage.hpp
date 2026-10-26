#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/TradingSession.hpp"
#include "../messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// TradingSessionStatusMessage
class TradingSessionStatusMessage : public Payload {
  public:
    // The code that selects this message
    static constexpr PayloadCode message_type = TemplateId::TradingSessionStatusMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    TradingSessionStatusMessage() = default;
    TradingSessionStatusMessage(std::chrono::nanoseconds timestamp, TradingSession trading_session);

    // Timestamp: Timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Trading Session: TradingSession
    TradingSession trading_session() const;
    void set_trading_session(TradingSession value);

    // Payload
    PayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PayloadVisitor& visitor) const override;
    std::unique_ptr<Payload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Payload& other) const override;

    bool operator==(const TradingSessionStatusMessage& other) const;
    bool operator!=(const TradingSessionStatusMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    TradingSession trading_session_{};
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
