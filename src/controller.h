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

//	int cecLogMessage(void *cbParam, const cec_log_message message) {return 0;}
//	int cecKeyPress(void *cbParam, const cec_keypress UNUSED(key)) {return 0;}
//	int cecCommand(void *cbParam, const cec_command UNUSED(command)) {return 0;}
//	int cecAlert(void *cbParam, const libcec_alert type, const libcec_parameter UNUSED(param)) {return 0;}

private:
	CEC::libcec_configuration cecConfig_;
	CEC::ICECCallbacks cecCallbacks_;
	CEC::ICECAdapter *parser_;
};

};

#endif //TVCONTROLSERVER_CONTROL_H
