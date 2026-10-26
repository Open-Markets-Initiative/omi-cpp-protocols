#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/PrimaryMarketCode.hpp"
#include "../enums/TestSecurityIndicator.hpp"
#include "../messages/Data.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class DataVisitor;

// This is the message format that will be used to disseminate all security symbols traded on
// MIAX Pearl Equities for the current trading session. The Symbol ID sent in this message will
// be disseminated in Depth of Market messages.
class SymbolUpdateMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SymbolUpdateMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 41;

    SymbolUpdateMessage() = default;
    SymbolUpdateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, const std::string& ticker_symbol, const std::array<std::byte, 1>& reserved_1, TestSecurityIndicator test_security_indicator, const std::array<std::byte, 1>& second_reserved_1, std::uint16_t lot_size, const std::string& opening_time, const std::string& closing_time, PrimaryMarketCode primary_market_code);

    // Nanoseconds: Nanosecond part of Matching Engine time.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Symbol Id: Symbol ID mapped to a given symbol. It is assigned per trading session and is
    // valid for that session.
    std::uint32_t symbol_id() const;
    void set_symbol_id(std::uint32_t value);

    // Ticker Symbol: Ticker symbol for the security in NASDAQ Integrated Platform format.
    const std::string& ticker_symbol() const;
    std::string& ticker_symbol();
    void set_ticker_symbol(const std::string& value);

    // Reserved 1: Reserved for future use.
    const std::array<std::byte, 1>& reserved_1() const;
    std::array<std::byte, 1>& reserved_1();
    void set_reserved_1(const std::array<std::byte, 1>& value);

    // Test Security Indicator: Y - Yes, N - No.
    TestSecurityIndicator test_security_indicator() const;
    void set_test_security_indicator(TestSecurityIndicator value);

    // Second Reserved 1: Reserved for future use.
    const std::array<std::byte, 1>& second_reserved_1() const;
    std::array<std::byte, 1>& second_reserved_1();
    void set_second_reserved_1(const std::array<std::byte, 1>& value);

    // Lot Size: Round Lot size in shares.
    std::uint16_t lot_size() const;
    void set_lot_size(std::uint16_t value);

    // Opening Time: Expressed in HH:MM:SS format. Eg: 04:00:00.
    const std::string& opening_time() const;
    std::string& opening_time();
    void set_opening_time(const std::string& value);

    // Closing Time: Expressed in HH:MM:SS format. Eg: 20:00:00.
    const std::string& closing_time() const;
    std::string& closing_time();
    void set_closing_time(const std::string& value);

    // Primary Market Code: Primary listing exchange code for the security.
    PrimaryMarketCode primary_market_code() const;
    void set_primary_market_code(PrimaryMarketCode value);

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

    bool operator==(const SymbolUpdateMessage& other) const;
    bool operator!=(const SymbolUpdateMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint32_t symbol_id_{};
    std::string ticker_symbol_{};
    std::array<std::byte, 1> reserved_1_{};
    TestSecurityIndicator test_security_indicator_{};
    std::array<std::byte, 1> second_reserved_1_{};
    std::uint16_t lot_size_{};
    std::string opening_time_{};
    std::string closing_time_{};
    PrimaryMarketCode primary_market_code_{};
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
