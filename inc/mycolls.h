#ifndef MYCOLLS_H
#include "object.h"

#ifdef WIN32
#define M_pAt(x) &items[x]
#else
#define M_pAt(x) pAt(x)
#endif

struct TCollection
{
  long limit;
  long count;
#ifdef WIN32
  LPObject *items;
#else
  HGLOBAL items;
#endif
  TCollection(long alimit);
  virtual ~TCollection();
#ifndef WIN32
  virtual TObject huge **pAt(long index);
#endif
  virtual LPObject at(long index);
  virtual void atremove(long index);
  virtual void atfree(long index);
  virtual void o_free(LPObject item);
  virtual void freeall();
  virtual void freeitem(LPObject item);
  virtual long atinsert(long index, LPObject item);
  virtual void remove(LPObject item);
  virtual void removeall();
  virtual long indexof(LPObject item);
  virtual long insert(LPObject item);
  virtual void pack();
  virtual void setlimit(long alimit);
};

struct TSortedCollection : TCollection
{
  int duplicates;

public:
  TSortedCollection(long alimit, int allowdupl);
  virtual int compare(void *key1, void *key2) = 0;
  virtual void *keyof(LPObject item);
  virtual int search(void *key, long *index); // returns boolean FALSE on not found
  virtual long insert(LPObject item);
  virtual long indexof(LPObject item);
  virtual long indexofpointer(LPObject item);
};

typedef TCollection *LPCollection;
typedef TSortedCollection *LPSortedCollection;

#define MYCOLLS_H
#endif
