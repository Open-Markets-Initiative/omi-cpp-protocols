#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EopType.hpp"
#include "../enums/LegalMarket.hpp"
#include "../messages/Message.hpp"
#include "../structs/Eop.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class Visitor;

// The EOP message contains expected opening price and size information for a security.
class ExpectedOpeningPriceAndSizeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExpectedOpeningPriceAndSizeMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 19;

    ExpectedOpeningPriceAndSizeMessage() = default;
    ExpectedOpeningPriceAndSizeMessage(std::uint32_t class_key, std::uint32_t security_id, const Eop& eop, std::uint32_t eos, EopType eop_type, LegalMarket legal_market);

    // Class Key: Class key
    std::uint32_t class_key() const;
    void set_class_key(std::uint32_t value);

    // Security Id: Product key
    std::uint32_t security_id() const;
    void set_security_id(std::uint32_t value);

    // Eop:
    const Eop& eop() const;
    Eop& eop();
    void set_eop(const Eop& value);

    // Eos: The expected opening size
    std::uint32_t eos() const;
    void set_eos(std::uint32_t value);

    // Eop Type:
    EopType eop_type() const;
    void set_eop_type(EopType value);

    // Legal Market:
    LegalMarket legal_market() const;
    void set_legal_market(LegalMarket value);

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

    bool operator==(const ExpectedOpeningPriceAndSizeMessage& other) const;
    bool operator!=(const ExpectedOpeningPriceAndSizeMessage& other) const;

  private:
    std::uint32_t class_key_{};
    std::uint32_t security_id_{};
    Eop eop_{};
    std::uint32_t eos_{};
    EopType eop_type_{};
    LegalMarket legal_market_{};
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
