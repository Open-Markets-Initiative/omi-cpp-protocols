#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// This group indicates the number of broken dates and references individual broken contracts
// in user defined tailor made repo. Applicable only to tailor made repos requested by traders
// with broken dates
class BrokenDatesGroup {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    BrokenDatesGroup() = default;
    BrokenDatesGroup(std::uint64_t broken_date_guid, std::int32_t broken_date_security_id, std::optional<std::uint16_t> broken_date_start, std::optional<std::uint16_t> broken_date_end);

    // Broken Date Guid: External unique broken date Instrument ID
    std::uint64_t broken_date_guid() const;
    void set_broken_date_guid(std::uint64_t value);

    // Broken Date Security Id: Broken date Instrument Globex Security ID
    std::int32_t broken_date_security_id() const;
    void set_broken_date_security_id(std::int32_t value);

    // Broken Date Start: Start date of a broken date period
    std::optional<std::uint16_t> broken_date_start() const;
    void set_broken_date_start(std::optional<std::uint16_t> value);

    // Broken Date End: End date of a broken date period
    std::optional<std::uint16_t> broken_date_end() const;
    void set_broken_date_end(std::optional<std::uint16_t> value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BrokenDatesGroup& other) const;
    bool operator!=(const BrokenDatesGroup& other) const;

  private:
    std::uint64_t broken_date_guid_{};
    std::int32_t broken_date_security_id_{};
    std::optional<std::uint16_t> broken_date_start_{};
    std::optional<std::uint16_t> broken_date_end_{};
};

std::ostream& operator<<(std::ostream& out, const BrokenDatesGroup& value);

} // namespace cme::globex::mdp3::sbe::v1_13
