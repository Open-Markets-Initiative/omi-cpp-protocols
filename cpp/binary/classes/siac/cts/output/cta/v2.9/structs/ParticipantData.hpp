#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../common/Decimal.hpp"
#include "../enums/Tick.hpp"

namespace siac::cts::output::cta::v2_9 {

// Participant Data
class ParticipantData {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 41;

    ParticipantData() = default;
    ParticipantData(std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, std::uint32_t total_volume_short, Tick tick);

    // Previous Close Price Date: Represents the date the security last traded
    std::uint32_t previous_close_price_date() const;
    void set_previous_close_price_date(std::uint32_t value);

    // Last Price: The Last Price represents the last price for that security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // High Price: The High Price represents the highest price paid for a security during the
    // trading day
    Decimal high_price() const;
    void set_high_price(Decimal value);

    // Low Price: The Low Price represents the lowest price paid for a security during the
    // trading day
    Decimal low_price() const;
    void set_low_price(Decimal value);

    // Open Price: The Open Price represents the first qualifying price paid for a security
    // during the trading day.
    Decimal open_price() const;
    void set_open_price(Decimal value);

    // Total Volume Short: Contains Total Volume of shares traded in a security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    std::uint32_t total_volume_short() const;
    void set_total_volume_short(std::uint32_t value);

    // Tick: Represents for a Participant the upward, downward or unchanged price movement in a
    // security's trades
    Tick tick() const;
    void set_tick(Tick value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ParticipantData& other) const;
    bool operator!=(const ParticipantData& other) const;

  private:
    std::uint32_t previous_close_price_date_{};
    Decimal last_price_{ 0, -6 };
    Decimal high_price_{ 0, -6 };
    Decimal low_price_{ 0, -6 };
    Decimal open_price_{ 0, -6 };
    std::uint32_t total_volume_short_{};
    Tick tick_{};
};

std::ostream& operator<<(std::ostream& out, const ParticipantData& value);

} // namespace siac::cts::output::cta::v2_9
