
#include "Transaction.h"
unsigned int Transaction::transaction_count {};

Transaction::Transaction(unsigned int arg_type)
{
  // to be implemented by the student*
  // both constructors
  Transaction::transaction_count++;
  this->tr_type = arg_type;
}

Transaction::Transaction
(unsigned int arg_type, Person& arg_sender, Person& arg_receiver,
 GPS_DD& arg_src_where, GPS_DD& arg_dst_where,
 IP_Address& arg_srcIP, IP_Address& arg_dstIP, time_t arg_when)
{
  // to be implemented by the student*
  //both constructors
  Transaction::transaction_count++;
  this->tr_type = arg_type;
  this->tr_sender = arg_sender;
  this->tr_receiver = arg_receiver;
  this->tr_src_where = arg_src_where;
  this->tr_dst_where = arg_dst_where;
  this->tr_srcIP = arg_srcIP;
  this->tr_dstIP = arg_dstIP;
  this->tr_when = arg_when;
}

void
Transaction::setData(void *arg_data)
{
  // to be implemented by the student*
  this->tr_data = arg_data;
}

void *
Transaction::getData(void)
{
  // to be implemented by the student*
  return this->tr_data;
}

double
Transaction::getDistance()
{
  // to be implemented by the student*
  return (tr_dst_where.distance(tr_src_where));
}

std::string
Transaction::description()
{
  std::string res;

  if (this->tr_sender == this->tr_receiver)
    {
      res += ("One-person Transaction for " + this->tr_sender.getName());
    }
  else
    {
      res += ("Two-persons Transaction for " + this->tr_sender.getName() + " and " + this->tr_receiver.getName());
    }

  res += (", Distance = " + std::to_string(this->getDistance()) + " miles.");
  return res;
}
