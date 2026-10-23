#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

namespace cme::globex::mdp3::sbe::v1_13 {

// Indicates the number of repeating symbols specified
class RelatedSymGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    RelatedSymGroup() = default;
    RelatedSymGroup(const std::string& symbol, std::int32_t security_id, std::optional<std::int32_t> order_qty, std::int8_t quote_type, std::optional<std::int8_t> side_optional, const std::array<std::byte, 2>& padding_2);

    // Symbol: Instrument Name or Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Order Qty: Quantity requested
    std::optional<std::int32_t> order_qty() const;
    void set_order_qty(std::optional<std::int32_t> value);

    // Quote Type: Type of quote requested
    std::int8_t quote_type() const;
    void set_quote_type(std::int8_t value);

    // Side Optional: Side requested
    std::optional<std::int8_t> side_optional() const;
    void set_side_optional(std::optional<std::int8_t> value);

    // Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& padding_2() const;
    std::array<std::byte, 2>& padding_2();
    void set_padding_2(const std::array<std::byte, 2>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RelatedSymGroup& other) const;
    bool operator!=(const RelatedSymGroup& other) const;

  private:
    std::string symbol_{};
    std::int32_t security_id_{};
    std::optional<std::int32_t> order_qty_{};
    std::int8_t quote_type_{};
    std::optional<std::int8_t> side_optional_{};
    std::array<std::byte, 2> padding_2_{};
};

std::ostream& operator<<(std::ostream& out, const RelatedSymGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
