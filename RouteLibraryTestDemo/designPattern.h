#pragma once
#include <iostream>


class  single
{
public:
	static single* getInstance()
	{
		if (m_data == nullptr)
		{
			m_data = new single();
		}
		return m_data;
	}
	single(single& other) = delete;
	single& operator = (single& other) = delete;
	~single()
	{
		delete m_data;
	}
protected:
private:
	single()
	{

	}
	static single*  m_data;
};

single* single::m_data = nullptr;


