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
//	cecCallbacks_.CBCecLogMessage  = &cecLogMessage;
//	cecCallbacks_.CBCecKeyPress    = &cecKeyPress;
//	cecCallbacks_.CBCecCommand     = &cecCommand;
//	cecCallbacks_.CBCecAlert       = &cecAlert;


	//setup config
	cecConfig_.Clear();
	cecConfig_.deviceTypes.Add(CEC::CEC_DEVICE_TYPE_PLAYBACK_DEVICE);
	snprintf(cecConfig_.strDeviceName, 13, "TV Control");
//	cecConfig_.clientVersion = CEC_CONFIG_VERSION;
	cecConfig_.bActivateSource = 0;
	cecConfig_.callbacks = 0;

	parser_ = static_cast<CEC::ICECAdapter *>(CECInitialise(&cecConfig_));
	if(!parser_)
	{
		std::cerr << "CECInitialise FAILED!!!" << std::endl;
		return;
	}
	CEC::cec_adapter_descriptor adapterDescriptor;
	int adapters = parser_->DetectAdapters(&adapterDescriptor, 1);
	if(adapters>0)
	{
		std::cout << "adapters = " << adapters << "===" << adapterDescriptor.strComPath << "===" << adapterDescriptor.strComName << std::endl;
		if(parser_->Open("RPI"))
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
