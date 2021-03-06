#include <iostream>
#include <windows.h>

class String
{
public: 
	explicit String (const char * string)
	{
		m_length = strlen(string);
		m_value = new char[m_length + 1];
		memcpy(m_value, string, m_length + 1);
	}

	~String()
	{
		delete[] m_value; 
	}

	String(const String& other)
	{
		Update(other);
	}

	operator const char*() const 
	{
		return m_value; 
	}

	String& operator=(const String& other)
	{
		if (this != &other)
		{
			delete[] m_value;
			Update(other);
		}
		return *this;
	}

	String operator+(const char* r_value) 
	{
		String tmp(*this);
		tmp += r_value;
		return tmp; 
	}

	String operator+(const String& r_value)
	{
		String tmp(*this);
		tmp += r_value;
		return tmp;
	}

	String& operator+=(const char* r_Value)
	{
		Concatenate(r_Value);
		return *this;
	}

	String& operator+=(const String& r_Value)
	{
		Concatenate(r_Value.m_value, r_Value.m_length);
		return *this;
	}

	size_t GetLength() const
	{
		return m_length; 
	}

	const char* c_str() const
	{
		return m_value; 
	}

	void Concatenate(const String& str)
	{
		Concatenate(str.m_value, str.m_length); 
	}

	void Concatenate(const char* str)
	{
		const auto n_length = strlen(str);
		Concatenate(str, n_length);
	}


private:
	char* m_value;
	size_t m_length;

	void Update(const String& str)
	{
		m_length = str.GetLength();
		m_value = new char[m_length + 1u];
		memcpy(m_value, str.c_str(), m_length + 1u);
	}

	void Concatenate(const char* str, const size_t length)
	{
		const auto n_string = new char[m_length + length + 1];
		memcpy(n_string, m_value, m_length);
		memcpy(n_string + m_length, str, length + 1);
		delete[] m_value;
		m_value = n_string;
		m_length += length;
	}
};

int main()
{
	String myString("Hello");
	myString.Concatenate("World");
	myString.Concatenate(myString);
	std::cout << myString.c_str() << std::endl; 
	String otherString(myString);
	std::cout << otherString.c_str() << std::endl; 
	String yetAnotherString("AnotherWorld");
	otherString = yetAnotherString;
	std::cout << otherString.c_str();

	String s1("Hello");
	const String s2("World");
	s1 += s2;				// operator+= for String
	std::cout << "HelloWorld = " << s1 << std::endl; 
	String s3 = s1 + s2;		// operator+ for String
	std::cout << "HelloWorldWorld = " << s3 << std::endl; 
	s3 += "Hello";			// operator+= for const char*
	std::cout << "HelloWorldWorldHello = " << s3 << std::endl; 
	const String s4 = s3 + "World";	// operator+ for const char
	std::cout << "HelloWorldWorldHelloWorld = " << s4 << std::endl; 
	OutputDebugStringA(s4);		// conversion function
}