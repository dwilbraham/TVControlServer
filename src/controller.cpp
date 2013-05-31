#include <iostream>
#include <stdio.h>

#include "controller.h"

using namespace TVControlServer;

Controller::Controller() :
	cecConfig_()
	,cecCallbacks_()
	,parser_(0)
{
	std::cout << "Hello Controller" << std::endl;

	//setup callbacks
	cecCallbacks_.Clear();
	cecCallbacks_.CBCecLogMessage  = &Controller::cecLogMessage;
	cecCallbacks_.CBCecKeyPress    = &Controller::cecKeyPress;
	cecCallbacks_.CBCecCommand     = &Controller::cecCommand;
	cecCallbacks_.CBCecAlert       = &Controller::cecAlert;


	//setup config
	cecConfig_.Clear();
	cecConfig_.deviceTypes.Add(CEC::CEC_DEVICE_TYPE_PLAYBACK_DEVICE);
	snprintf(cecConfig_.strDeviceName, 13, "TV Control");
	cecConfig_.clientVersion = CEC::CEC_CLIENT_VERSION_CURRENT;
	cecConfig_.bActivateSource = 0;
	cecConfig_.callbacks = &cecCallbacks_;

	parser_ = static_cast<CEC::ICECAdapter *>(CECInitialise(&cecConfig_));
	if(!parser_)
	{
		std::cerr << "CECInitialise FAILED!!!" << std::endl;
		return;
	}
	parser_->InitVideoStandalone();

	CEC::cec_adapter_descriptor adapterDescriptor;
	int adapters = parser_->DetectAdapters(&adapterDescriptor, 1);
	if(adapters>0)
	{
		std::cout << "adapters = " << adapters << "===" << adapterDescriptor.strComPath << "===" << adapterDescriptor.strComName << std::endl;
		if(parser_->Open(adapterDescriptor.strComName))
		{
			std::cout << "OPENED" << std::endl;
		}
		else
		{
			std::cout << "FAILED TO OPEN!!!" << std::endl;
		}
	}
}

Controller::~Controller()
{
	parser_->Close();
	CECDestroy(parser_);
}

bool Controller::powerOnTV()
{
	return parser_->PowerOnDevices();
}

bool Controller::powerOffTV()
{
	return parser_->StandbyDevices(CEC::CECDEVICE_TV);
}

int Controller::cecLogMessage(void *cbParam, const CEC::cec_log_message message)
{
	std::cout << "Controller::cecLogMessage: " << message.message << std::endl;
	return 1;
}

int Controller::cecAlert(void *cbParam, const CEC::libcec_alert type, const CEC::libcec_parameter param)
{
	switch (type)
	{
		case CEC::CEC_ALERT_CONNECTION_LOST:
			std::cout << "Controller::cecAlert connection lost" << std::endl;
			break;
		default:
			break;
	}
	return 1;
}

