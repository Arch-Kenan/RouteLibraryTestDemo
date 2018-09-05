#pragma once
#include <iostream>
#include <mutex>
#include <atomic>



class  single
{
public:
	static single* getInstance();
	single(single& other) = delete;
	single& operator = (single& other) = delete;
	~single();
protected:
private:
	single();
	static single*  m_data; 
};



