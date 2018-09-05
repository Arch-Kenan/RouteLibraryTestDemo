#pragma once
#include "designPattern.h"


//std::atomic<single*>  single::m_data;
//std::mutex single::mutex;
single* single::m_data = nullptr;
single* single::getInstance()
{
	
	if (m_data == nullptr)
	{

		m_data = new single();
	}
	return m_data;
}
single::~single()
{
	delete m_data;
}

single::single()
{

}






