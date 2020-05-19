/*!
 * \file ParserFemas.h
 * \project	WonderTrader
 *
 * \author Wesley
 * \date 2020/03/30
 * 
 * \brief 
 */
#pragma once
#include "../Share/IParserApi.h"
#include "./ustptraderapi/USTPFtdcMduserApi.h"
#include <map>

NS_OTP_BEGIN
class WTSTickData;
NS_OTP_END

USING_NS_OTP;

class ParserFemas : public IParserApi, public CUstpFtdcMduserSpi
{
public:
	ParserFemas();
	virtual ~ParserFemas();

public:
	enum LoginStatus
	{
		LS_NOTLOGIN,
		LS_LOGINING,
		LS_LOGINED
	};

//IQuoteParser �ӿ�
public:
	virtual bool init(WTSParams* config) override;

	virtual void release() override;

	virtual bool connect() override;

	virtual bool disconnect() override;

	virtual bool isConnected() override;

	virtual void subscribe(const CodeSet &vecSymbols) override;
	virtual void unsubscribe(const CodeSet &vecSymbols) override;

	virtual void registerListener(IParserApiListener* listener) override;


//CUstpFtdcMdSpi �ӿ�
public:
	virtual void OnRspError( CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	virtual void OnFrontConnected();

	virtual void OnRspUserLogin( CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	virtual void OnFrontDisconnected( int nReason );

	virtual void OnRspUnSubMarketData( CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	virtual void OnRtnDepthMarketData( CUstpFtdcDepthMarketDataField *pDepthMarketData );

	virtual void OnRspSubMarketData( CUstpFtdcSpecificInstrumentField *pSpecificInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast );

	virtual void OnHeartBeatWarning( int nTimeLapse );

private:
	/*
	 *	���͵�¼����
	 */
	void ReqUserLogin();
	/*
	 *	����Ʒ������
	 */
	void SubscribeMarketData();
	/*
	 *	��������Ϣ
	 */
	bool IsErrorRspInfo(CUstpFtdcRspInfoField *pRspInfo);


private:
	uint32_t			m_uTradingDate;
	LoginStatus			m_loginState;
	CUstpFtdcMduserApi*	m_pUserAPI;

	std::string			m_strFrontAddr;
	std::string			m_strBroker;
	std::string			m_strUserID;
	std::string			m_strPassword;

	CodeSet				m_filterSubs;

	int					m_iRequestID;

	IParserApiListener*	m_parserSink;
	IBaseDataMgr*		m_pBaseDataMgr;
};
