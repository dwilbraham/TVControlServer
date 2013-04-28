#ifndef TVCONTROLSERVER_CONTROL_H
#define TVCONTROLSERVER_CONTROL_H

#include <cec.h>

namespace TVControlServer
{

class Controller
{
public:
	Controller();
	~Controller();

	bool powerOnTV();
	bool powerOffTV();

	static int cecLogMessage(void *cbParam, const CEC::cec_log_message message);
	static int cecKeyPress(void *cbParam, const CEC::cec_keypress key) {return 0;}
	static int cecCommand(void *cbParam, const CEC::cec_command command) {return 0;}
	static int cecAlert(void *cbParam, const CEC::libcec_alert type, const CEC::libcec_parameter param) ;

private:
	CEC::libcec_configuration cecConfig_;
	CEC::ICECCallbacks cecCallbacks_;
	CEC::ICECAdapter *parser_;
};

};

#endif //TVCONTROLSERVER_CONTROL_H
