
#include "Person.h"
#define INET_ADDRSTRLEN    16
#define INET6_ADDRSTRLEN   46
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>
#define pi 3.14159265358979323846
unsigned int Person::person_count{};

GPS_DD::GPS_DD()
{
  // to be implemented by the student*
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longtitude)
{
  // to be implemented by the student*
  this->latitude = arg_latitude;
  this->longtitude = arg_longtitude;
}

double 
GPS_DD::getLatitude()
{
  // to be implemented by the student done*
  return this->latitude;
}
 
double
GPS_DD::getLongtitude
()
{
  // to be implemented by the student done*
  return this->longtitude;
}

// DD distance calculation
#include <math.h>
#define pi 3.14159265358979323846

double GeoDataSource_distance(double lat1, double lon1, double lat2, double lon2, char unit) 
{
  // to be implemented by the student*
  // for this homework, please use the source code shared by GeoDataSource under --
  // https://www.geodatasource.com/developers/c (you can copy and paste here)
  double deg2rad(double);
  double rad2deg(double);
  double theta, dist;
  
  if ((lat1 == lat2) && (lon1 == lon2)) {
    return 0;
  }
  else {
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'M':
        break;
      case 'K':
        dist = dist * 1.609344;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist);
  }
}

double deg2rad(double deg)
{
  return (deg * pi / 180);
}

double rad2deg(double rad)
{
  return (rad * 180 / pi);
}

double
GPS_DD::distance
(GPS_DD& another)
{
  // to be implemented by the student*
  return GeoDataSource_distance(this->getLatitude(), this->getLongtitude(), another.getLatitude(), another.getLongtitude(), 'M');
}

IP_Address::IP_Address()
{
  // to be implemented by the student*
}

IP_Address::IP_Address
(unsigned int arg_ip)
{
  // to be implemented by the student*
  this->addr = arg_ip;
}

std::string SDefault {"Default"};

std::string&
IP_Address::getIPaddressString()
{  
  return SDefault;
}

unsigned int
IP_Address::getIPaddressValue()
{
  // to be implemented by the student*
  return this->addr;
}

Person::Person()
{
  // to be implemented by the student*
  Person::person_count++;
}

Person::Person
(std::string arg_name, std::string arg_id)
{
  // to be implemented by the student*
  Person::person_count++;
  this->name = arg_name;
  this->vsID = arg_id;
}

void
Person::setHome
(std::string arg_home)
{
  // to be implemented by the student*
  this->hometown = arg_home;
}

void
Person::setHome
(GPS_DD arg_home)
{
  // to be implemented by the student*
  this->home = arg_home;
}

std::string
Person::getVsID()
{
  // to be implemented by the student*
  return this->vsID;
}

std::string
Person::getName()
{
  // to be implemented by the student*
  return this->name;
}

bool
Person::operator==
(Person& aPerson)
{
  // to be implemented by the student (if vsid are same return true)*
  if (this->vsID == aPerson.vsID)
  {
    return true;
  }
  else
  {
    return false;
  }
}

