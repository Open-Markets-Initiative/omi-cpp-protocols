#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/IsTestSymbol.hpp"
#include "../messages/Payload.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class PayloadVisitor;

// InstrumentDirectoryMessage
class InstrumentDirectoryMessage : public Payload {
  public:
    // The code that selects this message
    static constexpr PayloadCode message_type = TemplateId::InstrumentDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    InstrumentDirectoryMessage() = default;
    InstrumentDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, const std::string& symbol, const std::string& symbol_sfx, std::uint32_t round_lot, std::uint8_t reserved, IsTestSymbol is_test_symbol, Decimal mpv);

    // Timestamp: Timestamp
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Security Id: SecurityID
    std::uint16_t security_id() const;
    void set_security_id(std::uint16_t value);

    // Symbol: Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Symbol Sfx: SymbolSfx
    const std::string& symbol_sfx() const;
    std::string& symbol_sfx();
    void set_symbol_sfx(const std::string& value);

    // Round Lot: RoundLot
    std::uint32_t round_lot() const;
    void set_round_lot(std::uint32_t value);

    // Reserved: Reserved
    std::uint8_t reserved() const;
    void set_reserved(std::uint8_t value);

    // Is Test Symbol: IsTestSymbol
    IsTestSymbol is_test_symbol() const;
    void set_is_test_symbol(IsTestSymbol value);

    // Mpv: MPV
    Decimal mpv() const;
    void set_mpv(Decimal value);

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

    bool operator==(const InstrumentDirectoryMessage& other) const;
    bool operator!=(const InstrumentDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint16_t security_id_{};
    std::string symbol_{};
    std::string symbol_sfx_{};
    std::uint32_t round_lot_{};
    std::uint8_t reserved_{};
    IsTestSymbol is_test_symbol_{};
    Decimal mpv_{ 0, -6 };
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
