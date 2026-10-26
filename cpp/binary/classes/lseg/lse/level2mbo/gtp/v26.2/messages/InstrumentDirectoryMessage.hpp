#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/AllowedBookTypes.hpp"
#include "../common/Decimal.hpp"
#include "../enums/SourceVenue.hpp"
#include "../messages/Message.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

class Visitor;

// Used to disseminate a common and limited set of data for all configured instrument types,
// except strategy instruments, on the real-time channels.
class InstrumentDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::InstrumentDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 138;

    InstrumentDirectoryMessage() = default;
    InstrumentDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint64_t instrument, const std::string& isin, const AllowedBookTypes& allowed_book_types, SourceVenue source_venue, const std::string& venue_instrument_id, const std::string& tick_id, const std::array<std::byte, 8>& reserved_8, Decimal dynamic_circuit_breaker_tolerances, Decimal static_circuit_breaker_tolerances, const std::string& segment, const std::array<std::byte, 12>& reserved_12, const std::array<std::byte, 11>& reserved_11, const std::string& currency, char partition_id, const std::array<std::byte, 4>& reserved_4, Decimal average_daily_turnover_adt, const std::array<std::byte, 8>& second_reserved_8, const std::array<std::byte, 1>& reserved_1, const std::array<std::byte, 8>& third_reserved_8, const std::array<std::byte, 8>& fourth_reserved_8);

    // Timestamp: Time the message was generated.
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument: GTP Instrument identifier.
    std::uint64_t instrument() const;
    void set_instrument(std::uint64_t value);

    // Isin: ISIN Code of an instrument.
    const std::string& isin() const;
    std::string& isin();
    void set_isin(const std::string& value);

    // Allowed Book Types: Defines the order-book types that are allowed for the instrument
    const AllowedBookTypes& allowed_book_types() const;
    AllowedBookTypes& allowed_book_types();
    void set_allowed_book_types(const AllowedBookTypes& value);

    // Source Venue: Venue from which market data is received for the instrument.
    SourceVenue source_venue() const;
    void set_source_venue(SourceVenue value);

    // Venue Instrument Id: Instrument identifier used by the source venue.
    const std::string& venue_instrument_id() const;
    std::string& venue_instrument_id();
    void set_venue_instrument_id(const std::string& value);

    // Tick Id: The tick structure applicable for the instrument.
    const std::string& tick_id() const;
    std::string& tick_id();
    void set_tick_id(const std::string& value);

    // Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& reserved_8() const;
    std::array<std::byte, 8>& reserved_8();
    void set_reserved_8(const std::array<std::byte, 8>& value);

    // Dynamic Circuit Breaker Tolerances: Dynamic Circuit Breaker Tolerance (%) of the
    // instrument.
    Decimal dynamic_circuit_breaker_tolerances() const;
    void set_dynamic_circuit_breaker_tolerances(Decimal value);

    // Static Circuit Breaker Tolerances: Static Circuit Breaker Tolerance (%) of the
    // instrument.
    Decimal static_circuit_breaker_tolerances() const;
    void set_static_circuit_breaker_tolerances(Decimal value);

    // Segment: Segment the instrument is assigned to.
    const std::string& segment() const;
    std::string& segment();
    void set_segment(const std::string& value);

    // Reserved 12: Reserved for future use.
    const std::array<std::byte, 12>& reserved_12() const;
    std::array<std::byte, 12>& reserved_12();
    void set_reserved_12(const std::array<std::byte, 12>& value);

    // Reserved 11: Reserved for future use.
    const std::array<std::byte, 11>& reserved_11() const;
    std::array<std::byte, 11>& reserved_11();
    void set_reserved_11(const std::array<std::byte, 11>& value);

    // Currency: Currency Code as per ISO 4217.
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Partition Id: Trading System's partition in which the instrument is traded.
    char partition_id() const;
    void set_partition_id(char value);

    // Reserved 4: Reserved for future use.
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Average Daily Turnover Adt: Not Applicable to LSE.
    Decimal average_daily_turnover_adt() const;
    void set_average_daily_turnover_adt(Decimal value);

    // Second Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& second_reserved_8() const;
    std::array<std::byte, 8>& second_reserved_8();
    void set_second_reserved_8(const std::array<std::byte, 8>& value);

    // Reserved 1: Reserved for future use.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Third Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& third_reserved_8() const;
    std::array<std::byte, 8>& third_reserved_8();
    void set_third_reserved_8(const std::array<std::byte, 8>& value);

    // Fourth Reserved 8: Reserved for future use.
    const std::array<std::byte, 8>& fourth_reserved_8() const;
    std::array<std::byte, 8>& fourth_reserved_8();
    void set_fourth_reserved_8(const std::array<std::byte, 8>& value);

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

    bool operator==(const InstrumentDirectoryMessage& other) const;
    bool operator!=(const InstrumentDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint64_t instrument_{};
    std::string isin_{};
    AllowedBookTypes allowed_book_types_{};
    SourceVenue source_venue_{};
    std::string venue_instrument_id_{};
    std::string tick_id_{};
    std::array<std::byte, 8> reserved_8_{};
    Decimal dynamic_circuit_breaker_tolerances_{ 0, -8 };
    Decimal static_circuit_breaker_tolerances_{ 0, -8 };
    std::string segment_{};
    std::array<std::byte, 12> reserved_12_{};
    std::array<std::byte, 11> reserved_11_{};
    std::string currency_{};
    char partition_id_{};
    std::array<std::byte, 4> reserved_4_{};
    Decimal average_daily_turnover_adt_{ 0, -4 };
    std::array<std::byte, 8> second_reserved_8_{};
    std::array<std::byte, 1> reserved_1_{};
    std::array<std::byte, 8> third_reserved_8_{};
    std::array<std::byte, 8> fourth_reserved_8_{};
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
