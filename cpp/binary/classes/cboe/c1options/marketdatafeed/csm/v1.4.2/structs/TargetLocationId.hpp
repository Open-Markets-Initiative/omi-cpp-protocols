#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Target Location Id
class TargetLocationId {
  public:

    TargetLocationId() = default;
    TargetLocationId(std::uint8_t target_location_id_length, const std::string& target_location_id_text);

    // Target Location Id Length:
    std::uint8_t target_location_id_length() const;
    void set_target_location_id_length(std::uint8_t value);

    // Target Location Id Text:
    const std::string& target_location_id_text() const;
    std::string& target_location_id_text();
    void set_target_location_id_text(const std::string& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const TargetLocationId& other) const;
    bool operator!=(const TargetLocationId& other) const;

  private:
    std::uint8_t target_location_id_length_{};
    std::string target_location_id_text_{};
};

std::ostream& operator<<(std::ostream& out, const TargetLocationId& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
