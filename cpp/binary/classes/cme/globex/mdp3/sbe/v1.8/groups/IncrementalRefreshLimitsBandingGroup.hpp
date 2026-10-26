#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

#include "../common/Decimal.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// Number of entries in Market Data message
class IncrementalRefreshLimitsBandingGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 32;

    IncrementalRefreshLimitsBandingGroup() = default;
    IncrementalRefreshLimitsBandingGroup(std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::int32_t security_id, std::uint32_t rpt_seq);

    // High Limit Price: Allowable high limit price for the trading day
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Allowable low limit price for the trading day
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding.
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Security Id: Unique instrument ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshLimitsBandingGroup& other) const;
    bool operator!=(const IncrementalRefreshLimitsBandingGroup& other) const;

  private:
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshLimitsBandingGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_8
