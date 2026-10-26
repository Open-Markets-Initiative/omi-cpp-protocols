#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include "../common/Decimal.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// noUnderlyings
class DeprecatedUnderlyingsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 44;

    DeprecatedUnderlyingsGroup() = default;
    DeprecatedUnderlyingsGroup(std::uint64_t underlying_security_id, std::optional<Decimal> index_pct, std::optional<Decimal> index_theoretical_qty, const std::string& underlying_symbol);

    // Underlying Security Id: Underlying instrument's security ID.
    std::uint64_t underlying_security_id() const;
    void set_underlying_security_id(std::uint64_t value);

    // Index Pct: Required if this is an equity index instrument. Indicates the percentage that
    // this underlying composes the index.
    std::optional<Decimal> index_pct() const;
    void set_index_pct(std::optional<Decimal> value);

    // Index Theoretical Qty: The theoretical quantity of this underlying composing the index.
    // This tag is only used for index instruments.
    std::optional<Decimal> index_theoretical_qty() const;
    void set_index_theoretical_qty(std::optional<Decimal> value);

    // Underlying Symbol: Underlying instrument's ticker symbol.
    const std::string& underlying_symbol() const;
    std::string& underlying_symbol();
    void set_underlying_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const DeprecatedUnderlyingsGroup& other) const;
    bool operator!=(const DeprecatedUnderlyingsGroup& other) const;

  private:
    std::uint64_t underlying_security_id_{};
    std::optional<Decimal> index_pct_{};
    std::optional<Decimal> index_theoretical_qty_{};
    std::string underlying_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const DeprecatedUnderlyingsGroup& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
