#include "inc/globals.h"
#include "inc/mycolls.h"

/*
Purpose:
-------

This unit implements a subset of the OWL 1.0 TCollection
and TSortedCollection type's functionality, with increased capacity.

Fast binary TSortedCollection Search method.

Duplicates behaves differently from vanilla TSortedCollection.  It does
not replace the existing entry.

Limitations:
-----------

There are no stream handling methods such as Store

The Error method is here, but does nothing but produce a TCollection
runtime error when called.

*/

TSortedCollection::TSortedCollection(long alimit, int allowdupl) : TCollection(alimit)
{

  duplicates = allowdupl;
}

long TSortedCollection::indexof(LPObject item)
{

  long i;

  return ((search(keyof(item), &i)) ? i : -1);
}

long _inline TSortedCollection::indexofpointer(LPObject item)
{
  return TCollection::indexof(item);
}

int TSortedCollection::search(void *key, long *index)
{
  // Binary search for rapid insertion in sorted TCollections
  // searches for key.  Returns TRUE if key found, FALSE otherwise
  // Returns position of key in index, or place key should be inserted
  LONG u, l, t, o, r;

  r = t = -1;
  *index = 0;

  if (count)
  {
    u = count;
    l = 0;

    do
    {
      o = t;
      t = (l + u) / 2;

      r = compare(key, keyof(at(t)));

      if (r < 1)
        u = t;
      else
        l = t;

    } while ((r != 0) && (o != t));

    if (r > 0)
      t++;

    *index = t;

    return (r == 0);
  }

  return (FALSE);
}

long TSortedCollection::insert(LPObject item)
{
  long i;

  // May allow duplicates
  if ((!search(keyof(item), &i) || duplicates))
  {
    atinsert(i, item);
    return (i);
  }
  else
  {
    return (-1 * (i + 1));
  }
}

void inline *TSortedCollection::keyof(LPObject item)
{
  return (item);
}

TCollection::TCollection(long alimit)
{
  // There's no error trapping here, unfortunately.  Must test for items being 0 elsewhere
  items = 0;
  count = 0;
  setlimit(alimit);
}

TCollection::~TCollection()
{
  freeall();
#ifndef WIN32
  do
  {
  } while (GlobalUnlock(items));
  GlobalFree(items);
#endif
}

#ifndef WIN32
TObject huge **TCollection::pAt(long index)
{

  TObject huge **list;
  TObject huge **t;

  list = (TObject huge **)GlobalLock(items);

  if (list)
  {
    t = &list[index];
    GlobalUnlock(items);
    return t;
  }
  else
    return NULL;
}
#endif

TObject inline *TCollection::at(long index)
{
#ifdef WIN32
  LPObject *t;
#else
  TObject huge **t;
#endif
  t = M_pAt(index);
  return (t == NULL ? NULL : (LPObject)*t);
}

void TCollection::atremove(long index)
{
#ifdef WIN32
  LPObject *p;
#else
  TObject huge **p;
#endif
  long n;

  for (n = index; n < count; n++)
  {
    p = M_pAt(n);
    *p = at(n + 1);
  }
  p = M_pAt(count);
  *p = NULL;
  count--;
}

void TCollection::atfree(long index)
{
  freeitem(at(index));
  atremove(index);
}

void TCollection::o_free(LPObject item)
{
  remove(item);
  freeitem(item);
}

void TCollection::freeall()
{
  long n;

  if (count)
    for (n = (count - 1); n >= 0; n--)
      atfree(n);
}

void TCollection::freeitem(LPObject item)
{
  if (item)
    delete item;
}

long TCollection::atinsert(long index, LPObject item)
{
#ifdef WIN32
  LPObject *p;
#else
  TObject huge **p;
#endif

  long n;

  if ((limit - count) < 2)
    setlimit(limit * 2);

  for (n = count; n > index; n--)
  {
    p = M_pAt(n);
    *p = at(n - 1);
  }

  p = M_pAt(index);
  *p = item;

  count++;

  return index;
}

void TCollection::remove(LPObject item)
{
  atremove(indexof(item));
}

void TCollection::removeall(void)
{
  long n;

  if (count)
    for (n = (count - 1); n >= 0; n--)
      atremove(n);
}

long TCollection::indexof(LPObject item)
{
  long n, t;

  t = -1;
  n = 0;

  while ((t == -1) && (n < count))
  {
    if (item == at(n))
      t = n;
    else
      n++;
  }

  return t;
}

long TCollection::insert(LPObject item)
{
  atinsert(count, item);
  return count;
}

void TCollection::pack(void)
{
  setlimit(count + 50);
}

#ifdef WIN32
void TCollection::setlimit(long alimit)
{
  LPObject *t;

  if (items)
  {

    if (alimit > count)
    {

      t = (LPObject *)realloc(items, alimit * sizeof(LPObject));

      if (t)
      {
        items = t;
        limit = alimit;
      }
    }
  }
  else
  {

    t = (LPObject *)malloc(alimit * sizeof(LPObject));

    if (t)
    {
      limit = alimit;
      items = t;
    }
  }
}

#else

void TCollection::setlimit(long alimit)
{

  HGLOBAL t;

  if (items)
  {

    if (alimit > count)
    {

      t = GlobalReAlloc(items, alimit * sizeof(LPObject),
                        GMEM_MOVEABLE | GMEM_ZEROINIT);

      if (t)
      {
        items = t;
        limit = alimit;
      }
    }
  }
  else
  {

    t = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, alimit * sizeof(LPObject));

    if (t)
    {
      limit = alimit;
      items = t;
    }
  }
}
#endif
