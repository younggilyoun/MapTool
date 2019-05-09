// ���������� - Singleton
// ���α׷��� �ϳ��� �ν��Ͻ��� �����Ǵ� ����
#pragma once

#include <stdio.h>
#include <assert.h>

template <typename T>
class MySingleton
{
private:
	static T*	m_pInstance;
protected:
	MySingleton(void) { assert(!m_pInstance); };
	virtual ~MySingleton(void) {}

public:
	static T* GetInstance(void);
	void Destroy(void);
};


template <typename T>
T*	MySingleton<T>::m_pInstance = NULL;


template <typename T>
T* MySingleton<T>::GetInstance()
{
	if( !m_pInstance )
	{
		m_pInstance = new T;	
	}

	return m_pInstance;
}

template <typename T>
void MySingleton<T>::Destroy()
{
	if( m_pInstance )
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}