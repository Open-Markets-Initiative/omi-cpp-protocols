// Databento.MarketData.Normalized.Dbn.v1: messages/StatusMsg.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../enums/IsQuoting.hpp"
#include "../enums/IsShortSellRestricted.hpp"
#include "../enums/IsTrading.hpp"
#include "../enums/StatusAction.hpp"
#include "../enums/StatusReason.hpp"
#include "../enums/TradingEvent.hpp"
#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class Visitor;

// A trading status update message; the record of the status schema
class StatusMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::Status;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 24;

    StatusMsg() = default;
    StatusMsg(std::optional<std::chrono::nanoseconds> ts_recv, StatusAction status_action, StatusReason status_reason, TradingEvent trading_event, IsTrading is_trading, IsQuoting is_quoting, IsShortSellRestricted is_short_sell_restricted, const std::array<std::byte, 7>& reserved_7);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Status Action: The type of status change
    StatusAction status_action() const;
    void set_status_action(StatusAction value);

    // Status Reason: Additional details about the cause of the status change
    StatusReason status_reason() const;
    void set_status_reason(StatusReason value);

    // Trading Event: Further information about a status update
    TradingEvent trading_event() const;
    void set_trading_event(TradingEvent value);

    // Is Trading: The state of trading in the instrument
    IsTrading is_trading() const;
    void set_is_trading(IsTrading value);

    // Is Quoting: The state of quoting in the instrument
    IsQuoting is_quoting() const;
    void set_is_quoting(IsQuoting value);

    // Is Short Sell Restricted: The state of short sell restrictions for the instrument
    IsShortSellRestricted is_short_sell_restricted() const;
    void set_is_short_sell_restricted(IsShortSellRestricted value);

    // Reserved 7: Reserved, 7 bytes
    const std::array<std::byte, 7>& reserved_7() const;
    std::array<std::byte, 7>& reserved_7();
    void set_reserved_7(const std::array<std::byte, 7>& value);

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

    bool operator==(const StatusMsg& other) const;
    bool operator!=(const StatusMsg& other) const;

  private:
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    StatusAction status_action_{};
    StatusReason status_reason_{};
    TradingEvent trading_event_{};
    IsTrading is_trading_{};
    IsQuoting is_quoting_{};
    IsShortSellRestricted is_short_sell_restricted_{};
    std::array<std::byte, 7> reserved_7_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
