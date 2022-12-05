#ifndef IOSTRATEGY_HPP_
#define IOSTRATEGY_HPP_

class IoStrategy{
public:
    virtual void Read() const=0;
    virtual void Write() const=0;
};

#endif