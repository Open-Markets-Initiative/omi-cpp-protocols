#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace databento::marketdata::normalized::dbn::v3 {

// The resolution of a symbol for a date range
class MappingInterval {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 79;

    MappingInterval() = default;
    MappingInterval(std::uint32_t start_date, std::uint32_t end_date, const std::string& mapped_symbol);

    // Start Date: The UTC start date of the mapping interval, as a YYYYMMDD integer
    std::uint32_t start_date() const;
    void set_start_date(std::uint32_t value);

    // End Date: The UTC end date of the mapping interval, as a YYYYMMDD integer
    std::uint32_t end_date() const;
    void set_end_date(std::uint32_t value);

    // Mapped Symbol: The resolved symbol for this interval
    const std::string& mapped_symbol() const;
    std::string& mapped_symbol();
    void set_mapped_symbol(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MappingInterval& other) const;
    bool operator!=(const MappingInterval& other) const;

  private:
    std::uint32_t start_date_{};
    std::uint32_t end_date_{};
    std::string mapped_symbol_{};
};

std::ostream& operator<<(std::ostream& out, const MappingInterval& value);

} // namespace databento::marketdata::normalized::dbn::v3
