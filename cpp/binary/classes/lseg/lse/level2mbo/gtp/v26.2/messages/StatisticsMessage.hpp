#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/SourceVenue.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Contains a set of statistics that are updated frequently, usually as a result of executions.
class StatisticsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StatisticsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 74;

    StatisticsMessage() = default;
    StatisticsMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, SourceVenue source_venue, Decimal volume, Decimal volume_on_book_only, Decimal vwap, Decimal vwap_on_book_only, std::uint32_t number_of_trades, std::uint32_t number_of_trades_on_book_only, Decimal turnover, Decimal turnover_on_book_only);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Volume: Cumulative volume of all trades for the trading day.
    Decimal volume() const;
    void set_volume(Decimal value);

    // Volume On Book Only: Cumulative volume for the trading day excluding off-book trades.
    Decimal volume_on_book_only() const;
    void set_volume_on_book_only(Decimal value);

    // Vwap: Volume weighted average price for the day for all trades.
    Decimal vwap() const;
    void set_vwap(Decimal value);

    // Vwap On Book Only: Volume weighted average price for the day excluding off-book trades.
    Decimal vwap_on_book_only() const;
    void set_vwap_on_book_only(Decimal value);

    // Number Of Trades: Count of all trades for the day.
    std::uint32_t number_of_trades() const;
    void set_number_of_trades(std::uint32_t value);

    // Number Of Trades On Book Only: Count of trades for the day excluding off-book trades.
    std::uint32_t number_of_trades_on_book_only() const;
    void set_number_of_trades_on_book_only(std::uint32_t value);

    // Turnover: Turnover of all trades for the day.
    Decimal turnover() const;
    void set_turnover(Decimal value);

    // Turnover On Book Only: Turnover for the day excluding off-book trades.
    Decimal turnover_on_book_only() const;
    void set_turnover_on_book_only(Decimal value);

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

    bool operator==(const StatisticsMessage& other) const;
    bool operator!=(const StatisticsMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t instrument_{};
    SourceVenue source_venue_{};
    Decimal volume_{ 0, -4 };
    Decimal volume_on_book_only_{ 0, -4 };
    Decimal vwap_{ 0, -4 };
    Decimal vwap_on_book_only_{ 0, -4 };
    std::uint32_t number_of_trades_{};
    std::uint32_t number_of_trades_on_book_only_{};
    Decimal turnover_{ 0, -4 };
    Decimal turnover_on_book_only_{ 0, -4 };
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
