#include "cafe/EventWeight.hpp"

ClassImp(EventWeight);

EventWeight::EventWeight():  
  _name("default"),_weight(1),_weight_pos(1),_weight_neg(1)
{}

EventWeight::EventWeight(std::string name, double weight, 
			 double weight_pos, double weight_neg)
{
  Set(name, weight, weight_pos, weight_neg);
}

void EventWeight::Set(std::string name, double weight, 
			 double weight_pos, double weight_neg)
{
  _name       = name;
  _weight     = weight;
  _weight_pos = weight_pos;
  _weight_neg = weight_neg;
}

EventWeight::~EventWeight()
{}
