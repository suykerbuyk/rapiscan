/*
 * =====================================================================================
 *
 *       Filename:  rapiscan.cpp
 *
 *    Description:  OSI Screen
 *
 *        Version:  1.0
 *        Created:  09/27/2013 06:25:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Suykerbuyk
 *   Organization:  
 *
 * =====================================================================================
 */
#define _WITH_GETLINE
#include <iostream>
#include <string>
#include <sstream>


/* 
 * Implement the following function in C++ .
 * “bool F(string s, char ch1, char ch2, int n)”
 * The function determines whether or not there exists an occurrence of ch1 and ch2 
 * separated by a distance of no more than n in the given string s, where s is ascii 
 * and user entered (your function needs to work on any input.) The function must be 
 * efficient and **optimized** for both space and time. Please state what the 
 * complexity of your solution is.
 *
 * Examples:
 * “abcdefg”, ‘b’, ‘d’, 2 --> true
 * “abcdefg”, ‘b’, ‘d’, 20 --> true
 * “abcdefg”, ‘b’, ‘e’, 1 --> false
 */

typedef std::string string;
typedef std::stringstream stringstream;
using   std::getline;
using   std::cout;
using   std::cerr;
using   std::cin;
using   std::endl;

class RapiScanCheck
{
	public:
		RapiScanCheck():m_ch1(0), m_ch2(0), m_span(0) {};
		virtual ~RapiScanCheck() {}
		void ParseCommandLine (int arg, const char** argv);
		bool CheckIt(void);
		const string& GetRefString(void);
		void   SetRefString(const std::string& str) {m_str = str;}
		char   GetCh1(void); 
		void   SetCh1(const char& ch1) {m_ch1 = ch1;}
		char   GetCh2(void);
		void   SetCh2(const char& ch2)   {m_ch2 = ch2;}
		size_t GetSpan(void);
		void   SetSpan(const size_t& n) {m_span = n;}

	protected:
		bool GetStringFromUser (const string& msg, string& result);
		bool GetCharFromUser   (const string& msg,   char& result);
		bool GetNumberFromUser (const string& msg, size_t& result);
	private:
		string  m_str;
		char    m_ch1;
		char	m_ch2;
		size_t  m_span;
};

bool RapiScanCheck::GetStringFromUser(const string& msg, string& result)
{
	/* Don't overwrite an exiting value. Allows lazy initialization */
	if (!result.empty())
	{
		return(true);
	}
	cout << msg;
	getline(cin, result);
	if (result.empty() || result[0] == '\n')
	{
		return(false);
	}
	return(true);
}
bool RapiScanCheck::GetCharFromUser(const string& msg, char& result)
{
	/*  don't overwrite existing settings.  Allows lazy inits */
	if (0 != result)
	{
		return (true);
	}
	string input;
	if (!GetStringFromUser(msg, input))
		return(false);
	result = input[0];
	return true;
}
bool RapiScanCheck::GetNumberFromUser(const string& msg, size_t& result)
{
	/*  don't overwrite existing settings.  Allows lazy inits */
	if (0 != result)
	{
		return (true);
	}
	string input;
	if (!GetStringFromUser(msg, input))
		return(false);
	stringstream numeric(input);
	if (numeric >> result)
	{
		return true;
	}
	else
	{
		return false;
	}
}
const string& RapiScanCheck::GetRefString(void)
{
	if (!GetStringFromUser("Enter the reference string to scan: ", m_str))
		throw ("Did not receive valid user input in GetRefString!");
	return (m_str);
}

char RapiScanCheck::GetCh1(void)
{
	if (!GetCharFromUser("Enter the first character to parse for: ", m_ch1))
		throw("Did not receive valid user input in GetCh1!");
	return(m_ch1);
}
char RapiScanCheck::GetCh2(void)
{
	if (!GetCharFromUser("Enter the second character to parse for: ", m_ch2))
		throw("Did not receive valid user input in GetCh2!");
	return(m_ch2);
}
size_t RapiScanCheck::GetSpan(void)
{
	if (!GetNumberFromUser("Enter the maximum span of characters to search: ", m_span))
		throw("Did not receive valid user input in GetSpan!");
	return(m_span);
}

void RapiScanCheck::ParseCommandLine(int argc, const char** argv)
{
	if (argc > 1) m_str  =  argv[1];
	if (argc > 2) m_ch1  = *argv[2];
	if (argc > 3) m_ch2  = *argv[3];
	if (argc > 4) m_span = atoi(argv[4]);
}
bool RapiScanCheck::CheckIt(void)
{
	const string& ref  = GetRefString();
	const char    ch1  = GetCh1();
	const char    ch2  = GetCh2();
	const size_t  span = GetSpan();
	std::string::const_iterator itr1=ref.begin();
	std::string::const_iterator itr2=itr1;
	
	while (itr1 != ref.end())
	{
		if (*itr1++ == ch1)
		{
			size_t x = 0;
			itr2=itr1;
			while((itr2 != ref.end()) && (x++ < span))
			{
				if (*itr2++ == ch2)
					return (true);
			}
		}
	}
	return(false);
}


int main (int argc, const char** argv)
{
	RapiScanCheck rsc;
	rsc.ParseCommandLine(argc, argv);

	try
	{
		string result = rsc.CheckIt() ? "true" : "false";
		cout << " \"" << rsc.GetRefString() << "\", '" \
		     << rsc.GetCh1() << "', '" << rsc.GetCh2() << "', " \
		     << rsc.GetSpan() << " --> " << result << endl;
	}
	catch (const char* msg)
	{
		cerr << "ERROR:  " << msg << endl;
		exit (255);
	}

}
