// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: messages/InstrumentDirectoryMessage.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/IsTestSymbol.hpp"
#include "../messages/Message.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class Visitor;

// InstrumentDirectoryMessage
class InstrumentDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::InstrumentDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 36;

    InstrumentDirectoryMessage() = default;
    InstrumentDirectoryMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, const std::string& symbol, const std::string& symbol_sfx, std::uint32_t round_lot, const std::array<std::byte, 1>& reserved, IsTestSymbol is_test_symbol, Decimal mpv);

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
    const std::array<std::byte, 1>& reserved() const;
    std::array<std::byte, 1>& reserved();
    void set_reserved(const std::array<std::byte, 1>& value);

    // Is Test Symbol: IsTestSymbol
    IsTestSymbol is_test_symbol() const;
    void set_is_test_symbol(IsTestSymbol value);

    // Mpv: MPV
    Decimal mpv() const;
    void set_mpv(Decimal value);

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
    std::uint16_t security_id_{};
    std::string symbol_{};
    std::string symbol_sfx_{};
    std::uint32_t round_lot_{};
    std::array<std::byte, 1> reserved_{};
    IsTestSymbol is_test_symbol_{};
    Decimal mpv_{ 0, -6 };
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
