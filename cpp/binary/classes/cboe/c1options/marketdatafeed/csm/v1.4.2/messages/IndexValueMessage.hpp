#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>
#include <vector>

#include "../groups/IndexValueMdEntry.hpp"
#include "../messages/Message.hpp"
#include "../structs/Symbol.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// Index value messages contain the values associated with a calculated index. They are
// transmitted when an index is calculated.
class IndexValueMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::IndexValueMessage;

    IndexValueMessage() = default;
    IndexValueMessage(const Symbol& symbol, std::uint8_t no_entries, const std::vector<IndexValueMdEntry>& index_value_md_entry);

    // Symbol:
    const Symbol& symbol() const;
    Symbol& symbol();
    void set_symbol(const Symbol& value);

    // No Entries: Number of MDEntries in this message. Will not exceed 255
    std::uint8_t no_entries() const;
    void set_no_entries(std::uint8_t value);

    // Index Value Md Entry: Market data associated with the index
    const std::vector<IndexValueMdEntry>& index_value_md_entry() const;
    std::vector<IndexValueMdEntry>& index_value_md_entry();
    void set_index_value_md_entry(const std::vector<IndexValueMdEntry>& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const IndexValueMessage& other) const;
    bool operator!=(const IndexValueMessage& other) const;

  private:
    Symbol symbol_{};
    std::uint8_t no_entries_{};
    std::vector<IndexValueMdEntry> index_value_md_entry_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
