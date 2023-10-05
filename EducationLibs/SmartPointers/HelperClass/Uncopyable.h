#pragma once

class Uncopyable
{
  Uncopyable(const Uncopyable&){}
  Uncopyable& operator=(const Uncopyable&){}
protected:
  Uncopyable(){}
  ~Uncopyable(){}
};