#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Trade Condition
class TradeCondition {
  public:

    TradeCondition() = default;
    TradeCondition(std::uint8_t trade_condition_length, const std::string& trade_condition_text);

    // Trade Condition Length:
    std::uint8_t trade_condition_length() const;
    void set_trade_condition_length(std::uint8_t value);

    // Trade Condition Text:
    const std::string& trade_condition_text() const;
    std::string& trade_condition_text();
    void set_trade_condition_text(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TradeCondition& other) const;
    bool operator!=(const TradeCondition& other) const;

  private:
    std::uint8_t trade_condition_length_{};
    std::string trade_condition_text_{};
};

std::ostream& operator<<(std::ostream& out, const TradeCondition& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
