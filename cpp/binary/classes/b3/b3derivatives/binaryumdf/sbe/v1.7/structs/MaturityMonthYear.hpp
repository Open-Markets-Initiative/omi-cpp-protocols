// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: structs/MaturityMonthYear.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// SecurityDefinition_4Message
class MaturityMonthYear {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    MaturityMonthYear() = default;
    MaturityMonthYear(std::optional<std::uint16_t> year, std::optional<std::uint8_t> month, std::optional<std::uint8_t> day, std::optional<std::uint8_t> week);

    // Year: year
    std::optional<std::uint16_t> year() const;
    void set_year(std::optional<std::uint16_t> value);

    // Month: month
    std::optional<std::uint8_t> month() const;
    void set_month(std::optional<std::uint8_t> value);

    // Day: day
    std::optional<std::uint8_t> day() const;
    void set_day(std::optional<std::uint8_t> value);

    // Week: week
    std::optional<std::uint8_t> week() const;
    void set_week(std::optional<std::uint8_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MaturityMonthYear& other) const;
    bool operator!=(const MaturityMonthYear& other) const;

  private:
    std::optional<std::uint16_t> year_{};
    std::optional<std::uint8_t> month_{};
    std::optional<std::uint8_t> day_{};
    std::optional<std::uint8_t> week_{};
};

std::ostream& operator<<(std::ostream& out, const MaturityMonthYear& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
