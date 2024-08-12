unit RImpExp;

{ Import unit for the RIMPEXP.DLL filter utility functions }
{ library.  See RIMPEXP.H for documentation }

interface

uses WinTypes, MMSystem;

$IFNDEF WIN32
function GetINIFilePath: PChar;
$ENDIF

function SetBufSz(Sz: longint): longint;
function GetBufSz: longint;

function GetConfigInt(Section, Key: PChar; Default: integer): integer;
function GetConfigStr(Buf: PChar; szBuf: integer; Key, Section, Default: PChar): integer;
procedure SetConfigStr(Section, Key, Value: PChar);
procedure SetConfigInt(Section, Key: PChar; Value: integer;
procedure DeleteConfigTree(Section: PChar);

function WriteLine(FS: PMMIOINFO; text: PChar): integer;
function vMMIOprintf(FS: PMMIOINFO; format: PChar; var Arglist): integer;
function ReadLine(FS: PMMIOINFO; text: PChar; IsEoF: PBool): integer;

implementation

$IFNDEF WIN32
function GetINIFilePath;  external 'RImpExp';
$ENDIF

function GetConfigInt;    external 'RImpExp';
function GetConfigStr;    external 'RImpExp';
procedure SetConfigStr;    external 'RImpExp';
procedure SetConfigInt;    external 'RImpExp';
procedure DeleteConfigTree;    external 'RImpExp';

function SetBufSz;    external 'RImpExp';
function GetBufSz;    external 'RImpExp';

function WriteLine;   external 'RImpExp';
function vMMIOprintf; external 'RImpExp';
function ReadLine;    external 'RImpExp';

end.
