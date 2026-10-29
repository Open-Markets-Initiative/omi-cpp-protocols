#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../enums/Side.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// noSides
class CrossSidesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 22;

    CrossSidesGroup() = default;
    CrossSidesGroup(Side side, const std::array<std::byte, 1>& offset_1_padding_1, std::optional<std::uint32_t> account, std::optional<std::uint32_t> entering_firm_optional, std::uint64_t clordid, std::optional<std::uint32_t> trading_sub_account);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Offset 1 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_1_padding_1() const;
    std::array<std::byte, 1>& offset_1_padding_1();
    void set_offset_1_padding_1(const std::array<std::byte, 1>& value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Entering Firm Optional: enteringFirm
    std::optional<std::uint32_t> entering_firm_optional() const;
    void set_entering_firm_optional(std::optional<std::uint32_t> value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Trading Sub Account: tradingSubAccount
    std::optional<std::uint32_t> trading_sub_account() const;
    void set_trading_sub_account(std::optional<std::uint32_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const CrossSidesGroup& other) const;
    bool operator!=(const CrossSidesGroup& other) const;

  private:
    Side side_{};
    std::array<std::byte, 1> offset_1_padding_1_{};
    std::optional<std::uint32_t> account_{};
    std::optional<std::uint32_t> entering_firm_optional_{};
    std::uint64_t clordid_{};
    std::optional<std::uint32_t> trading_sub_account_{};
};

std::ostream& operator<<(std::ostream& out, const CrossSidesGroup& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
