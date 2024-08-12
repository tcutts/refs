#ifndef OBJECT_H

struct TObject
{
  TObject();
  virtual ~TObject();
};

typedef TObject *LPObject;

#define OBJECT_H
#endif
