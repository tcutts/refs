{*******************************************************}
{*                                                     *}
{*      IMPTFR.PAS - Reference import structure        *}
{*                                                     *}
{*      This file is (C) Tim Cutts 1993,1994 and may   *}
{*      not be redistributed in its present form,      *}
{*      except as part of a Refs Import DLL.  It       *}
{*      may be used, modified, in other programs.      *}
{*                                                     *}
{*******************************************************}

unit ImpTfr;

interface

{This is basically equivalent to TRef
 without the methods}

type
  PImportRef = ^TImportRef;
  TImportRef = record
  Result: Byte;
  RefType: Byte;
  Authors: PChar;
  Date: PChar;
  Title: PChar;
  Journal: PChar;
  Vol: PChar;
  VolNo: PChar;
  Pages: PChar;
  Text: PChar;
  Keywords: PChar;
  Publisher: PChar;
  City: PChar;
  Editor: PChar;
  SortStr: PChar;
  end;

implementation

end.
