#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

namespace cme::globex::mdp3::sbe::v1_13 {

// Number of scheduled Trading Dates
class TradingSessionsGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 18;

    TradingSessionsGroup() = default;
    TradingSessionsGroup(std::optional<std::uint16_t> trade_date, std::optional<std::uint16_t> settl_date, std::optional<std::uint16_t> maturity_date, const std::string& security_alt_id);

    // Trade Date: Trade Session Date
    std::optional<std::uint16_t> trade_date() const;
    void set_trade_date(std::optional<std::uint16_t> value);

    // Settl Date: Settle (Value) Date corresponding to Trade Date
    std::optional<std::uint16_t> settl_date() const;
    void set_settl_date(std::optional<std::uint16_t> value);

    // Maturity Date: Maturity Date
    std::optional<std::uint16_t> maturity_date() const;
    void set_maturity_date(std::optional<std::uint16_t> value);

    // Security Alt Id: Expanded instrument description. Will contain either ISIN or CUSIP
    const std::string& security_alt_id() const;
    std::string& security_alt_id();
    void set_security_alt_id(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TradingSessionsGroup& other) const;
    bool operator!=(const TradingSessionsGroup& other) const;

  private:
    std::optional<std::uint16_t> trade_date_{};
    std::optional<std::uint16_t> settl_date_{};
    std::optional<std::uint16_t> maturity_date_{};
    std::string security_alt_id_{};
};

std::ostream& operator<<(std::ostream& out, const TradingSessionsGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
