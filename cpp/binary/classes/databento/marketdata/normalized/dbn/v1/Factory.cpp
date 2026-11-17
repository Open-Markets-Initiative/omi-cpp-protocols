// Databento.MarketData.Normalized.Dbn.v1: Factory.cpp
#include "Factory.hpp"

#include "definitions.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case TradeMsg::message_type: return std::make_unique<TradeMsg>();
        case Mbp1Msg::message_type: return std::make_unique<Mbp1Msg>();
        case Mbp10Msg::message_type: return std::make_unique<Mbp10Msg>();
        case OhlcvMsg::message_type: return std::make_unique<OhlcvMsg>();
        case StatusMsg::message_type: return std::make_unique<StatusMsg>();
        case InstrumentDefMsg::message_type: return std::make_unique<InstrumentDefMsg>();
        case ImbalanceMsg::message_type: return std::make_unique<ImbalanceMsg>();
        case ErrorMsg::message_type: return std::make_unique<ErrorMsg>();
        case SymbolMappingMsg::message_type: return std::make_unique<SymbolMappingMsg>();
        case SystemMsg::message_type: return std::make_unique<SystemMsg>();
        case StatMsg::message_type: return std::make_unique<StatMsg>();
        case MboMsg::message_type: return std::make_unique<MboMsg>();
        case Cmbp1Msg::message_type: return std::make_unique<Cmbp1Msg>();
        case CbboMsg::message_type: return std::make_unique<CbboMsg>();
        case BboMsg::message_type: return std::make_unique<BboMsg>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<GatewayMessage> GatewayMessageFactory::create(GatewayMessageCode code) {
    switch (code) {
        case RecordBodyTradeMsg::message_type: return std::make_unique<RecordBodyTradeMsg>();
        case RecordBodyMbp1Msg::message_type: return std::make_unique<RecordBodyMbp1Msg>();
        case RecordBodyMbp10Msg::message_type: return std::make_unique<RecordBodyMbp10Msg>();
        case RecordBodyOhlcvMsg::message_type: return std::make_unique<RecordBodyOhlcvMsg>();
        case RecordBodyStatusMsg::message_type: return std::make_unique<RecordBodyStatusMsg>();
        case RecordBodyInstrumentDefMsg::message_type: return std::make_unique<RecordBodyInstrumentDefMsg>();
        case RecordBodyImbalanceMsg::message_type: return std::make_unique<RecordBodyImbalanceMsg>();
        case RecordBodyErrorMsg::message_type: return std::make_unique<RecordBodyErrorMsg>();
        case RecordBodySymbolMappingMsg::message_type: return std::make_unique<RecordBodySymbolMappingMsg>();
        case RecordBodySystemMsg::message_type: return std::make_unique<RecordBodySystemMsg>();
        case RecordBodyStatMsg::message_type: return std::make_unique<RecordBodyStatMsg>();
        case RecordBodyMboMsg::message_type: return std::make_unique<RecordBodyMboMsg>();
        case RecordBodyCmbp1Msg::message_type: return std::make_unique<RecordBodyCmbp1Msg>();
        case RecordBodyCbboMsg::message_type: return std::make_unique<RecordBodyCbboMsg>();
        case RecordBodyBboMsg::message_type: return std::make_unique<RecordBodyBboMsg>();
        default: return std::make_unique<UnknownGatewayMessage>(code);
    }
}

} // namespace databento::marketdata::normalized::dbn::v1
