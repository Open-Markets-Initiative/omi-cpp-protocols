#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class Visitor;

// A symbol mapping message, which maps a symbol of one SType to another
class SymbolMappingMsg : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = Rtype::SymbolMapping;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 64;

    SymbolMappingMsg() = default;
    SymbolMappingMsg(const std::string& stype_in_symbol, const std::string& stype_out_symbol, const std::array<std::byte, 4>& dummy_4, std::optional<std::chrono::nanoseconds> start_ts, std::optional<std::chrono::nanoseconds> end_ts);

    // Stype In Symbol: The input symbol
    const std::string& stype_in_symbol() const;
    std::string& stype_in_symbol();
    void set_stype_in_symbol(const std::string& value);

    // Stype Out Symbol: The output symbol
    const std::string& stype_out_symbol() const;
    std::string& stype_out_symbol();
    void set_stype_out_symbol(const std::string& value);

    // Dummy 4: Reserved, 4 bytes
    const std::array<std::byte, 4>& dummy_4() const;
    std::array<std::byte, 4>& dummy_4();
    void set_dummy_4(const std::array<std::byte, 4>& value);

    // Start Ts: The start of the mapping interval expressed as the number of nanoseconds since
    // the UNIX epoch
    std::optional<std::chrono::nanoseconds> start_ts() const;
    void set_start_ts(std::optional<std::chrono::nanoseconds> value);

    // End Ts: The end of the mapping interval expressed as the number of nanoseconds since the
    // UNIX epoch
    std::optional<std::chrono::nanoseconds> end_ts() const;
    void set_end_ts(std::optional<std::chrono::nanoseconds> value);

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

    bool operator==(const SymbolMappingMsg& other) const;
    bool operator!=(const SymbolMappingMsg& other) const;

  private:
    std::string stype_in_symbol_{};
    std::string stype_out_symbol_{};
    std::array<std::byte, 4> dummy_4_{};
    std::optional<std::chrono::nanoseconds> start_ts_{};
    std::optional<std::chrono::nanoseconds> end_ts_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
