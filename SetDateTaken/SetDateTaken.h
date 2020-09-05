/////////////////////////////////////////////////////////////////////////////
// Copyright � by W. T. Block, all rights reserved
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "resource.h"
#include "KeyedCollection.h"
#include <vector>
#include <map>
#include <memory>
#include <gdiplus.h>

// we need to link to the GDI+ library
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// this class creates a fast look up of the mime type and class ID as 
// defined by GDI+ for common file extensions
class CDate
{
	// protected definition
protected:
	typedef struct tagMonthLookup
	{
		CString m_csMonth;
		int m_nMonth;

	} MONTH_LOOKUP;

	typedef enum
	{
		tnYear = 0,
		tnMonth = tnYear + 1,
		tnDay = tnMonth + 1,
		tnHour = tnDay + 1,
		tnMinute = tnHour + 1,
		tnSecond = tnMinute + 1,
	} TOKEN_NAME;

	// protected data
protected:
	// date formatted as a string
	CString m_csDate;

	// The date and time when the original image data was generated.
	// For a digital still camera, this is the date and time the picture 
	// was taken or recorded. The format is "YYYY:MM:DD HH:MM:SS" with time 
	// shown in 24-hour format, and the date and time separated by one blank 
	// character (hex 20).
	CString m_csDateTaken;

	// 4 digit year
	int m_nYear;

	// month as a number (1..12)
	int m_nMonth;

	// day of the month (0..31)
	int m_nDay;

	// hour of the day (0..23)
	int m_nHour;

	// minute of the hour (0..59)
	int m_nMinute;

	// second of the minute (0..59)
	int m_nSecond;

	// boolean indicator that all is well
	bool m_bOkay;

	// rapid month lookup
	CKeyedCollection<CString, int> m_MonthLookup;

	// public properties
public:
	// date and time formatted as a string
	inline CString GetDate()
	{
		CString value;
		COleDateTime oDT = DateAndTime;
		COleDateTime::DateTimeStatus eStatus = oDT.GetStatus();
		bool bOkay = COleDateTime::DateTimeStatus::valid == eStatus;

		// if the status is good, format into a string
		if ( bOkay )
		{
			value = oDT.Format( _T( "%Y:%m:%d %H:%M:%S" ) );
			m_csDate = value;
		}

		return m_csDate;
	}
	// date and time formatted as a string
	inline void SetDate( CString value )
	{
		COleDateTime oDT;
		if ( oDT.ParseDateTime( value ) )
		{
			DateAndTime = oDT;
			Okay = true;
			m_csDate = value;
		}
	}
	// date and time formatted as a string
	__declspec( property( get = GetDate, put = SetDate ) )
		CString Date;

	// 4 digit year
	inline int GetYear()
	{
		return m_nYear;
	}
	// 4 digit year
	inline void SetYear( int value )
	{
		m_nYear = value;
	}
	// 4 digit year
	__declspec( property( get = GetYear, put = SetYear ) )
		int Year;

	// month of the year as a number (1..12)
	inline int GetMonth()
	{
		return m_nMonth;
	}
	// month of the year as a number (1..12)
	inline void SetMonth( int value )
	{
		m_nMonth = value;
	}
	// month of the year as a number (1..12)
	__declspec( property( get = GetMonth, put = SetMonth ) )
		int Month;

	// day of the month (0..31)
	inline int GetDay()
	{
		return m_nDay;
	}
	// day of the month (0..31)
	inline void SetDay( int value )
	{
		m_nDay = value;
	}
	// day of the month (0..31)
	__declspec( property( get = GetDay, put = SetDay ) )
		int Day;

	// hour of the day (0..23)
	inline int GetHour()
	{
		return m_nHour;
	}
	// hour of the day (0..23)
	inline void SetHour( int value )
	{
		m_nHour = value;
	}
	// hour of the day (0..23)
	__declspec( property( get = GetHour, put = SetHour ) )
		int Hour;

	// minute of the hour (0..59)
	inline int GetMinute()
	{
		return m_nMinute;
	}
	// minute of the hour (0..59)
	inline void SetMinute( int value )
	{
		m_nMinute = value;
	}
	// minute of the hour (0..59)
	__declspec( property( get = GetMinute, put = SetMinute ) )
		int Minute;

	// second of the minute (0..59)
	inline int GetSecond()
	{
		return m_nSecond;
	}
	// second of the minute (0..59)
	inline void SetSecond( int value )
	{
		m_nSecond = value;
	}
	// second of the minute (0..59)
	__declspec( property( get = GetSecond, put = SetSecond ) )
		int Second;

	// boolean indicator that all is well
	inline bool GetOkay()
	{
		COleDateTime oDT( Year, Month, Day, Hour, Minute, Second );
		COleDateTime::DateTimeStatus eStatus = oDT.GetStatus();
		Okay = COleDateTime::DateTimeStatus::valid == eStatus;
		return m_bOkay;
	}
	// boolean indicator that all is well
	inline void SetOkay( bool value )
	{
		m_bOkay = value;
	}
	// boolean indicator that all is well
	__declspec( property( get = GetOkay, put = SetOkay ) )
		bool Okay;

	// gets the date and time from the properties
	inline COleDateTime GetDateAndTime()
	{
		COleDateTime value( Year, Month, Day, Hour, Minute, Second );
		COleDateTime::DateTimeStatus eStatus = value.GetStatus();
		Okay = COleDateTime::DateTimeStatus::valid == eStatus;
		return value;
	}
	// sets the date and time if valid
	inline void SetDateAndTime( COleDateTime value )
	{
		COleDateTime::DateTimeStatus eStatus = value.GetStatus();
		bool bOkay = COleDateTime::DateTimeStatus::valid == eStatus;
		if ( bOkay )
		{
			Year = value.GetYear();
			Month = value.GetMonth();
			Day = value.GetDay();
			Hour = value.GetHour();
			Minute = value.GetMinute();
			Second = value.GetSecond();
			Okay = bOkay;
		}
	}
	// date and time property
	__declspec( property( get = GetDateAndTime, put = SetDateAndTime ) )
		COleDateTime DateAndTime;

	// The date and time when the original image data was generated.
	// For a digital still camera, this is the date and time the picture 
	// was taken or recorded. The format is "YYYY:MM:DD HH:MM:SS" with time 
	// shown in 24-hour format, and the date and time separated by one blank 
	// character (hex 20).
	inline CString GetDateTaken()
	{
		return m_csDateTaken;
	}
	// The date and time when the original image data was generated.
	// For a digital still camera, this is the date and time the picture 
	// was taken or recorded. The format is "YYYY:MM:DD HH:MM:SS" with time 
	// shown in 24-hour format, and the date and time separated by one blank 
	// character (hex 20).
	void SetDateTaken( CString csDate );
	// The date and time when the original image data was generated.
	// For a digital still camera, this is the date and time the picture 
	// was taken or recorded. The format is "YYYY:MM:DD HH:MM:SS" with time 
	// shown in 24-hour format, and the date and time separated by one blank 
	// character (hex 20).
	__declspec( property( get = GetDateTaken, put = SetDateTaken ) )
		CString DateTaken;

	// public methods
public:
	// return the month of the year (1..12) given the month's name
	// or return 0 if one is not found
	int GetMonthOfTheYear( CString month )
	{
		int value = 0;

		// the key is the first three characters in lower case
		const CString csKey = month.Left( 3 ).MakeLower();

		// if the key exists in the cross reference, then lookup the
		// month of the year (1..12)
		if ( m_MonthLookup.Exists[ csKey ] )
		{
			value = *m_MonthLookup.find( csKey );
		}

		return value;
	}

	// constructor
	CDate()
	{
		Year = -1;
		Month = -1;
		Day = -1;
		Hour = 0;
		Minute = 0;
		Second = 0;

		// create a lookup table for months
		LPCTSTR months[] =
		{
			_T( "jan" ),
			_T( "feb" ),
			_T( "mar" ),
			_T( "apr" ),
			_T( "may" ),
			_T( "jun" ),
			_T( "jul" ),
			_T( "aug" ),
			_T( "sep" ),
			_T( "oct" ),
			_T( "nov" ),
			_T( "dec" ),
		};
		const int nMonths = _countof( months );
		for ( int nMonth = 0; nMonth < nMonths; nMonth++ )
		{
			m_MonthLookup.add
			(
				months[ nMonth ],
				new int( nMonth + 1 )
			);
		}

		Okay = false;
	}
};

////////////////////////////////////////////////////////////////////////////
// this class creates a fast look up of the mime type and class ID as 
// defined by GDI+ for common file extensions
class CExtension
{
	// protected definitions
protected:
	typedef struct tagExtensionLookup
	{
		CString m_csFileExtension;
		CString m_csMimeType;

	} EXTENSION_LOOKUP;

	typedef struct tagClassLookup
	{
		CString m_csMimeType;
		CLSID m_ClassID;

	} CLASS_LOOKUP;

	// protected data
protected:
	// current file extension
	CString m_csFileExtension;

	// current mime type
	CString m_csMimeType;

	// current class ID
	CLSID m_ClassID;

	// cross reference of file extensions to mime types
	CKeyedCollection<CString, CString> m_mapExtensions;

	// cross reference of mime types to class IDs
	CKeyedCollection<CString, CLSID> m_mapMimeTypes;

	// public properties
public:
	// current file extension
	inline CString GetFileExtension()
	{
		return m_csFileExtension;
	}
	// current file extension
	void SetFileExtension( CString value );
	// current file extension
	__declspec( property( get = GetFileExtension, put = SetFileExtension ) )
		CString FileExtension;

	// image extension associated with the current file extension
	inline CString GetMimeType()
	{
		return m_csMimeType;
	}
	// image extension associated with the current file extension
	inline void SetMimeType( CString value )
	{
		m_csMimeType = value;
	}
	// get image extension associated with the current file extension
	__declspec( property( get = GetMimeType, put = SetMimeType ) )
		CString MimeType;

	// class ID associated with the current file extension
	inline CLSID GetClassID()
	{
		return m_ClassID;
	}
	// class ID associated with the current file extension
	inline void SetClassID( CLSID value )
	{
		m_ClassID = value;
	}
	// class ID associated with the current file extension
	__declspec( property( get = GetClassID, put = SetClassID ) )
		CLSID ClassID;

	// public methods
public:

	// protected methods
protected:

	// public virtual methods
public:

	// protected virtual methods
protected:

	// public construction
public:
	CExtension()
	{
		// extension conversion table
		static EXTENSION_LOOKUP ExtensionLookup[] =
		{
			{ _T( ".bmp" ), _T( "image/bmp" ) },
			{ _T( ".dib" ), _T( "image/bmp" ) },
			{ _T( ".rle" ), _T( "image/bmp" ) },
			{ _T( ".gif" ), _T( "image/gif" ) },
			{ _T( ".jpeg" ), _T( "image/jpeg" ) },
			{ _T( ".jpg" ), _T( "image/jpeg" ) },
			{ _T( ".jpe" ), _T( "image/jpeg" ) },
			{ _T( ".jfif" ), _T( "image/jpeg" ) },
			{ _T( ".png" ), _T( "image/png" ) },
			{ _T( ".tiff" ), _T( "image/tiff" ) },
			{ _T( ".tif" ), _T( "image/tiff" ) }
		};

		// build a cross reference of file extensions to 
		// mime types
		const int nPairs = _countof( ExtensionLookup );
		for ( int nPair = 0; nPair < nPairs; nPair++ )
		{
			const CString csKey =
				ExtensionLookup[ nPair ].m_csFileExtension;

			CString* pValue = new CString
			(
				ExtensionLookup[ nPair ].m_csMimeType
			);

			// add the pair to the collection
			m_mapExtensions.add( csKey, pValue );
		}
	}
};

/////////////////////////////////////////////////////////////////////////////
// used for gdiplus library
ULONG_PTR m_gdiplusToken;

/////////////////////////////////////////////////////////////////////////////
// this class records the date and time information in each image file 
// referenced
CDate m_Date;

/////////////////////////////////////////////////////////////////////////////
// this class creates a fast look up of the mime type and class ID as 
// defined by GDI+ for common file extensions
CExtension m_Extension;

/////////////////////////////////////////////////////////////////////////////
// 4 digit year command line parameter
int m_nYear;

/////////////////////////////////////////////////////////////////////////////
// month of the year command line parameter (1..12)
int m_nMonth;

/////////////////////////////////////////////////////////////////////////////
// day of the month command line parameter (0..31)
int m_nDay;

/////////////////////////////////////////////////////////////////////////////
// the new folder under the image folder to contain the corrected images
static inline CString GetCorrectedFolder()
{
	return _T( "Corrected" );
}

/////////////////////////////////////////////////////////////////////////////
// the new folder under the image folder to contain the corrected images
static inline int GetCorrectedFolderLength()
{
	const CString csFolder = GetCorrectedFolder();
	const int value = csFolder.GetLength();
	return value;
}

/////////////////////////////////////////////////////////////////////////////
// This function creates a file system folder whose fully qualified 
// path is given by pszPath. If one or more of the intermediate 
// folders do not exist, they will be created as well. 
// returns true if the path is created or already exists
bool CreatePath( LPCTSTR pszPath )
{
	if ( ERROR_SUCCESS == SHCreateDirectoryEx( NULL, pszPath, NULL ) )
	{
		return true;
	}

	return false;
} // CreatePath

/////////////////////////////////////////////////////////////////////////////
// initialize GDI+
bool InitGdiplus()
{
	GdiplusStartupInput gdiplusStartupInput;
	Status status = GdiplusStartup
	(
		&m_gdiplusToken,
		&gdiplusStartupInput,
		NULL
	);
	return ( Ok == status );
} // InitGdiplus

/////////////////////////////////////////////////////////////////////////////
// remove reference to GDI+
void TerminateGdiplus()
{
	GdiplusShutdown( m_gdiplusToken );
	m_gdiplusToken = NULL;

}// TerminateGdiplus

/////////////////////////////////////////////////////////////////////////////
