
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind/bind.hpp>
using namespace boost::placeholders;
#include <boost/thread.hpp>

#include <string>
#include <vector>
#include "plog/Log.h"


namespace pentair_control {
typedef boost::shared_ptr<boost::asio::serial_port> serial_port_ptr;

#define SERIAL_PORT_READ_BUF_SIZE 256

class SerialPort
{
protected:
	boost::asio::io_service& io_service_;
	serial_port_ptr port_;
	boost::mutex mutex_;

	char read_buf_raw_[SERIAL_PORT_READ_BUF_SIZE];
	std::string read_buf_str_;

	char end_of_line_char_;

private:
	SerialPort(const SerialPort &p);
	SerialPort &operator=(const SerialPort &p);

public:
	SerialPort(boost::asio::io_service& io_service);
	virtual ~SerialPort(void);

	char end_of_line_char() const;
	void end_of_line_char(const char &c);

	virtual bool start(const std::string& com_port_name, int baud_rate=9600);
	virtual void stop();

	int write_some(const std::string &buf);
	int write_some(const char *buf, const int &size);


protected:
	virtual void async_read_some_();
	virtual void on_receive_(const boost::system::error_code& ec, size_t bytes_transferred);
	virtual void on_receive_(const std::string &data);

};
};
