#pragma once

#include <memory>

#include "messages/Message.hpp"
#include "messages/AdministrativeMessagePayload.hpp"
#include "messages/ControlMessagePayload.hpp"
#include "messages/EquityAndIndexLastSaleMessagePayload.hpp"
#include "messages/OpenInterestMessagePayload.hpp"
#include "messages/EquityAndIndexEndOfDaySummaryMessagePayload.hpp"
#include "messages/LongEquityAndIndexQuoteMessagePayload.hpp"
#include "messages/ShortEquityAndIndexQuoteMessagePayload.hpp"
#include "messages/UnderlyingValueMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

// Makes the message a Message Category selects. A code the specification does
// not list makes an UnknownMessage carrying that code, never nothing, so a stream never
// stops on one.
class Factory {
  public:
    static std::unique_ptr<Message> create(MessageCode code);
};

// Makes the message a Administrative Message Type selects. A code the specification does
// not list makes an UnknownAdministrativeMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class AdministrativeMessagePayloadFactory {
  public:
    static std::unique_ptr<AdministrativeMessagePayload> create(AdministrativeMessagePayloadCode code);
};

// Makes the message a Control Message Type selects. A code the specification does
// not list makes an UnknownControlMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class ControlMessagePayloadFactory {
  public:
    static std::unique_ptr<ControlMessagePayload> create(ControlMessagePayloadCode code);
};

// Makes the message a Equity And Index Last Sale Message Type selects. A code the specification does
// not list makes an UnknownEquityAndIndexLastSaleMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class EquityAndIndexLastSaleMessagePayloadFactory {
  public:
    static std::unique_ptr<EquityAndIndexLastSaleMessagePayload> create(EquityAndIndexLastSaleMessagePayloadCode code);
};

// Makes the message a Open Interest Message Type selects. A code the specification does
// not list makes an UnknownOpenInterestMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class OpenInterestMessagePayloadFactory {
  public:
    static std::unique_ptr<OpenInterestMessagePayload> create(OpenInterestMessagePayloadCode code);
};

// Makes the message a Equity And Index End Of Day Summary Message Type selects. A code the specification does
// not list makes an UnknownEquityAndIndexEndOfDaySummaryMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class EquityAndIndexEndOfDaySummaryMessagePayloadFactory {
  public:
    static std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> create(EquityAndIndexEndOfDaySummaryMessagePayloadCode code);
};

// Makes the message a Long Equity And Index Quote Message Type selects. A code the specification does
// not list makes an UnknownLongEquityAndIndexQuoteMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class LongEquityAndIndexQuoteMessagePayloadFactory {
  public:
    static std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> create(LongEquityAndIndexQuoteMessagePayloadCode code);
};

// Makes the message a Short Equity And Index Quote Message Type selects. A code the specification does
// not list makes an UnknownShortEquityAndIndexQuoteMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class ShortEquityAndIndexQuoteMessagePayloadFactory {
  public:
    static std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> create(ShortEquityAndIndexQuoteMessagePayloadCode code);
};

// Makes the message a Underlying Value Message Type selects. A code the specification does
// not list makes an UnknownUnderlyingValueMessagePayload carrying that code, never nothing, so a stream never
// stops on one.
class UnderlyingValueMessagePayloadFactory {
  public:
    static std::unique_ptr<UnderlyingValueMessagePayload> create(UnderlyingValueMessagePayloadCode code);
};

} // namespace siac::opra::output::obi::v6_2
